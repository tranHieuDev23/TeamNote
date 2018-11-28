const string OPERATOR = "+-*/^";

bool isNumber(char c)
{
    return '0' <= c && c <= '9';
}

bool isOperator(char c)
{
    return OPERATOR.find(c) != string::npos;
}

int precedence(char c)
{
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return 3;
}

bool isLeftToRight(char c)
{
    return c != '^';
}

long long calculate(long long valueLeft, char operat, long long valueRight)
{
    if (operat == '+')
        return valueLeft + valueRight;
    if (operat == '-')
        return valueLeft - valueRight;
    if (operat == '*')
        return valueLeft * valueRight;
    if (operat == '/')
        return valueLeft / valueRight;
    if (operat == '^')
        return power(valueLeft, valueRight);
}

stack<long long> valueStack;
stack<char> operatorStack;
pair<bool, long long> evaluate(const string &expression)
{   
    while(!valueStack.empty()) valueStack.pop();
    while(!operatorStack.empty()) operatorStack.pop();

    long long currentValue = 0;
    FOR(i, 0, int(expression.size()) - 1)
    {
        char c = expression[i];
        if (c == ' ')
            continue;
        if (isNumber(c))
        {
            currentValue = currentValue * 10 + c - '0';
            if (!isNumber(expression[i + 1]))
            {
                valueStack.push(currentValue);
                currentValue = 0;
            }
        }
        if (c == '(')
            operatorStack.push(c);
        if (c == ')')
        {
            while(true)
            {
                if (operatorStack.empty())
                    return mp(false, -1);
                c = operatorStack.top();
                operatorStack.pop();
                if (c == '(')
                    break;
                if (valueStack.size() < 2)
                    return mp(false, -1);
                long long valueRight = valueStack.top(); valueStack.pop();
                long long valueLeft = valueStack.top(); valueStack.pop();
                valueStack.push(calculate(valueLeft, c, valueRight));
            }
        }
        if (isOperator(c))
        {
            while(!operatorStack.empty())
            {
                char t = operatorStack.top();
                if (
                    t == '(' || 
                    precedence(t) < precedence(c) || 
                    (precedence(t) == precedence(c) && !isLeftToRight(t))
                )
                    break;
                operatorStack.pop();
                if (valueStack.size() < 2)
                    return mp(false, -1);
                long long valueRight = valueStack.top(); valueStack.pop();
                long long valueLeft = valueStack.top(); valueStack.pop();
                valueStack.push(calculate(valueLeft, t, valueRight));
            }
            operatorStack.push(c);
        }
    }
    while(!operatorStack.empty())
    {
        char c = operatorStack.top();
        operatorStack.pop();
        if (c == '(' || valueStack.size() < 2)
            return mp(false, -1);
        long long valueRight = valueStack.top(); valueStack.pop();
        long long valueLeft = valueStack.top(); valueStack.pop();
        valueStack.push(calculate(valueLeft, c, valueRight));
    }
    if (valueStack.size() != 1)
        return mp(false, -1);
    long long result = valueStack.top(); valueStack.pop();
    return mp(true, result);
}