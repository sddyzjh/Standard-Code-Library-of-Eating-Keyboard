/// 表达式解析
/// 线性扫描, 直接计算.
/// 不支持三元运算符.
/// 一元运算符经过特殊处理. 它们不会(也不应)与二元运算符共用一种符号.

/// prio: 字符优先级. 在没有括号的约束下, 优先级高的优先计算.
/// pref: 结合顺序. pref[i] == true 表示从左到右结合, false 则为从右到左结合.
/// 圆括号运算符会特别对待.

/// 如果需要建树, 直接改Calc和Push函数.

/// ctt: 字符集编号下界.
/// ctf: 字符集编号上界.
/// ctx: 字符集大小.
const int ctf = -128;
const int ctt = 127;
const int ctx = ctt - ctf;

/// 表达式字符总数.
const int mxn = 1005000;

/// inp: 输入的表达式; 已经去掉了空格.
/// inpt: 输入的表达式的长度.
/// sx, aval: 由Destruct设定的外部变量数组. 无需改动.
/// 用法:
int len = Destruct(inp, inpt);
Evaluate(sx, len, aval);


/// 重新初始化: 调用Destruct即可.

////////////////////////////////////////////////////////////////////////

int _prio[ctx]; int* prio = _prio - ctf;
bool _pref[ctx]; bool* pref = _pref - ctf;

// 设置一个运算符的优先级和结合顺序.
void SetProp(char x, int a, int b) { prio[x] = a; pref[x] = b; }

stack<int> ap; // 变量栈.
stack<char> op; // 符号栈.

int Fetch() { int x = ap.top(); ap.pop(); return x; }
void Push(int x) { ap.push(x); }

/// 这个函数定义了如何处理栈内的实际元素.
void Calc()
{
    char cop = op.top(); op.pop();
    switch(cop)
    {
        case '+': { int b = Fetch(); int a = Fetch(); Push(a + b); } return;
        case '-': { int b = Fetch(); int a = Fetch(); Push(a - b); } return;
        case '*': { int b = Fetch(); int a = Fetch(); Push(a * b); } return;
        case '/': { int b = Fetch(); int a = Fetch(); Push(a / b); } return;
        case '|': { int b = Fetch(); int a = Fetch(); Push(a | b); } return;
        case '&': { int b = Fetch(); int a = Fetch(); Push(a & b); } return;
        case '^': { int b = Fetch(); int a = Fetch(); Push(a ^ b); } return;
        case '!': { int a = Fetch(); Push(a); } return;     // '+'的一元算符.
        case '~': { int a = Fetch(); Push(-a); } return;    // '-'的一元算符.
        default: return;
    }
}

/// s: 转化后的表达式, 其中0表示变量, 其它表示相应运算符.　len: 表达式长度.
/// g: 变量索引序列, 表示表达式从左到右的变量分别是哪个.
void Evaluate(char* s, int len, int* g)
{
    int gc = 0;
    for(int i=0; i<len; i++)
    {
        if(s[i] == 0) // 输入是一个变量. 一般可以直接按需求改掉, 例如 if(IsVar(s[i])).
        {
            Push(g[gc++]); // 第gc个变量的**值**入栈.
        }
        else // 输入是一个运算符s[i].
        {
            if(s[i] == '(') op.push(s[i]);
            else if(s[i] == ')')
            {
                while(op.top() != '(') Calc();
                op.pop();
            }
            else
            {
                while( prio[s[i]] < prio[op.top()] || 
                    (prio[s[i]] == prio[op.top()] && pref[s[i]] == true))
                    Calc();
                op.push(s[i]);
            }
        }
    }
}

/// 解析一个字符串, 得到能够被上面的函数处理的格式.
/// 对于这个函数而言, "变量"是某个十进制整数.
/// 有些时候输入本身就是这样的格式, 就不需要过多处理.
/// 支持的二元运算符: +, -, *, /, |, &, ^. 支持的一元运算符: +, -.
char sx[mxn]; // 表达式序列.
int aval[mxn]; // 数字. 这些是扔到变量栈里面的东西.
               // 可以直接写成某种place holder, 如果不关心这些变量之间的区别的话.
/// 返回: 表达式序列长度.
int Destruct(char* s, int len)
{
    int xlen = 0;
    sx[xlen++] = '(';
    bool cvr = false;
    int x = 0;
    int vt = 0;
    for(int i=0; i<len; i++)
    {
        if('0' <= s[i] && s[i] <= '9')
        {
            if(!cvr) sx[xlen++] = 0;
            cvr = true;
            if(cvr) x = x * 10 + s[i] - '0';
        }
        else
        {
            if(cvr) { aval[vt++] = x; x = 0; }
            cvr = false;
            sx[xlen++] = s[i];
        }
    }
    if(cvr) { aval[vt++] = x; x = 0; }
    
    for(int i=xlen; i>=1; i--) // 一元运算符特判, 修改成不同于二元运算符的符号.
        if((sx[i]=='+' || sx[i]=='-') && sx[i-1] != ')' && sx[i-1])
            sx[i] = sx[i] == '+' ? '!' : '~'; 
    
    sx[xlen++] = ')';
    return xlen;
}

char c[mxn];

char inp[mxn]; int inpt;
int main()
{
    SetProp('(', 0, true);
    SetProp(')', 0, true);
    
    SetProp('+', 10, true);
    SetProp('-', 10, true);
    
    SetProp('*', 100, true);
    SetProp('/', 100, true);
    
    SetProp('|', 1000, true);
    SetProp('&', 1001, true);
    SetProp('^', 1002, true);
    
    SetProp('!', 10000, false);
    SetProp('~', 10000, false);
    
    inpt = 0;
    char c;
    while((c = getchar()) != EOF && c != '\n' && c!='\r') if(c != ' ') inp[inpt++] = c;
    // 输入.
    printf("%s\n", inp);
    // 表达式符号.
    int len = Destruct(inp, inpt);
    for(int i=0; i<len; i++) if(sx[i] == 0) printf("."); else printf("%c", sx[i]); printf("\n");
    // 运算数.
    int t = 0; for(int i=0; i<len; i++) if(sx[i] == 0) printf("%d ", aval[t++]); printf("\n");
    Evaluate(sx, len, aval);
    // 结果.
    printf("%d\n", ap.top());
    
    return 0;
}

// (123+---213-+--321)+4*--57^6 = -159 correct!