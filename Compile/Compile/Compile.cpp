#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <string>
#include <fstream>

//各个单词的类
#define CONSTSYM 1
#define VARSYM 2
#define PROCEDURESYM 3
#define BEGINSYM 4
#define ENDSYM 5
#define ODDSYM 6
#define IFSYM 7
#define THENSYM 8
#define CALLSYM 9
#define WHILESYM 10
#define DOSYM 11
#define READSYM 12
#define WRITESYM 13
#define IDENT 14
#define NUMBER 15
#define EQUAL 16
#define SEPARATOR 17
#define LPAR 18
#define RPAR 19
#define PLUS 20
#define SUB 21
#define MUL 22
#define DIV 23
#define ASSIGNMENT 24
#define UNEQUAL 25
#define GREATER 26
#define EQUAL_GREATER 27
#define LESS 28
#define EQUAL_LESS 29

//操作指令
#define Opr_RET 0		// 过程返回
#define Opr_NEG 1		// 栈顶 := -栈顶
#define Opr_NOT 2		// 栈顶 := !栈顶
#define Opr_ADD 3		// 次栈顶 := 次栈顶 + 栈顶
#define Opr_SUB 4		// 次栈顶 := 次栈顶 - 栈顶
#define Opr_MUL 5		// 次栈顶 := 次栈顶 * 栈顶
#define Opr_DIV 6		// 次栈顶 := 次栈顶 / 栈顶
#define Opr_EQU 7		// 次栈顶 := (次栈顶 = 栈顶)
#define Opr_NEQ 8		// 次栈顶 := (次栈顶 != 栈顶)
#define Opr_LES 9		// 次栈顶 := (次栈顶 < 栈顶)
#define Opr_LEQ 10      // 次栈顶 := (次栈顶 <= 栈顶)
#define Opr_GTR 11		// 次栈顶 := (次栈顶 > 栈顶)
#define Opr_GEQ 12	    // 次栈顶 := (次栈顶 >= 栈顶)
#define Opr_PRT 13		// 栈顶的值输出至控制台屏幕
#define Opr_PNL 14		// 控制台屏幕输出一个换行
#define Opr_SCN 15		// 从控制台读取输入，植入栈顶

using namespace std;


map<string, int> SYM; //存放单词的类别
vector<string> ID; //存放用户定义标识符
vector<string> NUM; //存放用户定义的数
int pos_id = 0, pos_num = 0; //标识符表和数表的当前位置
map<string, int> KeyWord; //关键字表，每个关键字对应其类别编码
map<int, string> Code_SYM; //获取对应类别编码的字符串形式

ifstream InFile;
ofstream OutFile;
string IN = "";
string FileName[] = { "PL0_code.in", "PL0_code0.in", "PL0_code1.in", "PL0_code2.in", "PL0_code3.in" };
//string OutFile[] = { "code_out.txt", "code0_out.txt", "code1_out.txt", "code2_out.txt", "code3_out.txt" };
int POS = 0;
char ch;
struct triad
{
    int Kind;
    int Value;
    string Name;
};
vector<triad> Word;
struct Table_Element
{
    string Name;
    int Kind;
    int Level;
    int ADR = 0;
};
vector <Table_Element> TABLE;
struct code_data
{
    int Addr;
    string f;
    int l;
    int a;
};
int Cur_addr = 2;
vector<code_data> CODE;

int Assign_statement(int index,int Lev,int con); //赋值语句
int Condition_statement(int index,int Lev,int con);//条件语句
int Whilie_statement(int index,int Lev,int con);//当型循环语句
int Call_statement(int index,int Lev,int con); //过程调用语句
int Read_statement(int index,int Lev,int con); //读语句
int Write_statement(int index,int Lev,int con); //写语句
int Begin_end(int index,int Lev,int con); //复合语句
void initKeyWord() //初始化关键字表
{
    pair<string, int> tmp;
    pair<int, string> tmp2;
    tmp.first = "const", tmp.second = CONSTSYM;
    tmp2.first = CONSTSYM, tmp2.second = "CONSTSYM";
    KeyWord.insert(tmp), Code_SYM.insert(tmp2);
    tmp.first = "var", tmp.second = VARSYM;
    tmp2.first = VARSYM, tmp2.second = "VARSYM";
    KeyWord.insert(tmp), Code_SYM.insert(tmp2);
    tmp.first = "procedure", tmp.second = PROCEDURESYM;
    tmp2.first = PROCEDURESYM, tmp2.second = "PROCEDURESYM";
    KeyWord.insert(tmp), Code_SYM.insert(tmp2);
    tmp.first = "begin", tmp.second = BEGINSYM;
    tmp2.first = BEGINSYM, tmp2.second = "BEGINSYM";
    KeyWord.insert(tmp), Code_SYM.insert(tmp2);
    tmp.first = "end", tmp.second = ENDSYM;
    tmp2.first = ENDSYM, tmp2.second = "ENDSYM";
    KeyWord.insert(tmp), Code_SYM.insert(tmp2);
    tmp.first = "odd", tmp.second = ODDSYM;
    tmp2.first = ODDSYM, tmp2.second = "ODDSYM";
    KeyWord.insert(tmp), Code_SYM.insert(tmp2);
    tmp.first = "if", tmp.second = IFSYM;
    tmp2.first = IFSYM, tmp2.second = "IFSYM";
    KeyWord.insert(tmp), Code_SYM.insert(tmp2);
    tmp.first = "then", tmp.second = THENSYM;
    tmp2.first = THENSYM, tmp2.second = "THENSYM";
    KeyWord.insert(tmp), Code_SYM.insert(tmp2);
    tmp.first = "call", tmp.second = CALLSYM;
    tmp2.first = CALLSYM, tmp2.second = "CALLSYM";
    KeyWord.insert(tmp), Code_SYM.insert(tmp2);
    tmp.first = "while", tmp.second = WHILESYM;
    tmp2.first = WHILESYM, tmp2.second = "WHILESYM";
    KeyWord.insert(tmp), Code_SYM.insert(tmp2);
    tmp.first = "do", tmp.second = DOSYM;
    tmp2.first = DOSYM, tmp2.second = "DOSYM";
    KeyWord.insert(tmp), Code_SYM.insert(tmp2);
    tmp.first = "read", tmp.second = READSYM;
    tmp2.first = READSYM, tmp2.second = "READSYM";
    KeyWord.insert(tmp), Code_SYM.insert(tmp2);
    tmp.first = "write", tmp.second = WRITESYM;
    tmp2.first = WRITESYM, tmp2.second = "WRITESYM";
    KeyWord.insert(tmp), Code_SYM.insert(tmp2);
    tmp2.first = IDENT, tmp2.second = "IDENT";
    Code_SYM.insert(tmp2);
    tmp2.first = NUMBER, tmp2.second = "NUMBER";
    Code_SYM.insert(tmp2);
}
char GetChar() //从IN中读入一个字符
{
    if (POS < (int)IN.length()) return IN[POS++];
    else return '\0';
}
bool isChar(char c)
{
    return c >= 'a' && c <= 'z';
}
bool isNum(char c)
{
    return c >= '0' && c <= '9';
}
void ReSet() //回退字符指标并重置ch
{
    POS--;
    ch = NULL;
}
void GetBC()
{
    while (ch == ' ' || ch == '\n' || ch == NULL) {
        ch = GetChar();
    }
}
int Reserve(string str) //检查关键字,找到即返回对应编码，否则返回0
{
    map<string, int>::iterator iter = KeyWord.end();
    iter = KeyWord.find(str);
    if (iter != KeyWord.end()) return iter->second;
    else return 0;
}
int InsrID(string str)
{//将标识符插入表中并返回对应指针
    ID.push_back(str);
    return pos_id++;
}
int InsrNum(string str)
{//将常数插入表中并返回指针
    NUM.push_back(str);
    return pos_num++;
}
void GetSym()
{
    pos_id = pos_num = 0;
    POS = 0;
    int Len = IN.length();
    triad _word;
    Word.clear();
    while (POS < Len)
    {
        int code; //类别编码
        string ans = ""; //输出三元式
        string strToken = "";
        ch = GetChar();
        GetBC();
        if (isChar(ch))
        {
            while (isChar(ch) || isNum(ch))
            {
                strToken += ch;
                ch = GetChar();
            }
            ReSet();
            code = Reserve(strToken);
            if (code == 0) //不是关键字
            {
                //将标识符类放入SYM
                pair<string, int> tmp(strToken, IDENT);
                SYM.insert(tmp);
                //将标识符插入表ID
                int value = InsrID(strToken);
                _word.Kind = IDENT, _word.Value = value, _word.Name = strToken;
                Word.push_back(_word);
                cout << "< " << "IDENT" << ',' << value << ',' << strToken << " >\n";
            }
            else { //是关键字
                //将关键字类放入SYM
                pair<string, int> tmp(strToken, code);
                SYM.insert(tmp);
                _word.Kind = code, _word.Value = -1, _word.Name = strToken;
                Word.push_back(_word);
                cout << "< " << Code_SYM[code] << ',' << '-' << ',' << strToken << " >\n";
            }
        }
        else if (isNum(ch))
        {
            while (isNum(ch)) {
                strToken += ch;
                ch = GetChar();
            }
            ReSet();
            pair<string, int> tmp(strToken, NUMBER);
            SYM.insert(tmp);
            int value = InsrNum(strToken);
            _word.Kind = NUMBER, _word.Value = value, _word.Name = strToken;
            Word.push_back(_word);
            cout << "< " << "NUMBER" << ',' << value << ',' << strToken << " >\n";
        }
        else if (ch == '+') {
            strToken += ch;
            pair<string, int> tmp(strToken, PLUS);
            SYM.insert(tmp);
            _word.Kind = PLUS, _word.Value = -1, _word.Name = strToken;
            Word.push_back(_word);
            cout << "< " << "PLUS" << ',' << '-' << ',' << strToken << " >\n";
        }
        else if (ch == '-') {
            strToken += ch;
            pair<string, int> tmp(strToken, SUB);
            SYM.insert(tmp);
            _word.Kind = SUB, _word.Value = -1, _word.Name = strToken;
            Word.push_back(_word);
            cout << "< " << "SUB" << ',' << '-' << ',' << strToken << " >\n";
        }
        else if (ch == '*') {
            strToken += ch;
            pair<string, int> tmp(strToken, MUL);
            SYM.insert(tmp);
            _word.Kind = MUL, _word.Value = -1, _word.Name = strToken;
            Word.push_back(_word);
            cout << "< " << "MUL" << ',' << '-' << ',' << strToken << " >\n";
        }
        else if (ch == '/') {
            strToken += ch;
            pair<string, int> tmp(strToken, DIV);
            SYM.insert(tmp);
            _word.Kind = DIV, _word.Value = -1, _word.Name = strToken;
            Word.push_back(_word);
            cout << "< " << "DIV" << ',' << '-' << ',' << strToken << " >\n";
        }
        else if (ch == '=') {
            strToken += ch;
            pair<string, int> tmp(strToken, EQUAL);
            SYM.insert(tmp);
            _word.Kind = EQUAL, _word.Value = -1, _word.Name = strToken;
            Word.push_back(_word);
            cout << "< " << "EQUAL" << ',' << '-' << ',' << strToken << " >\n";
        }
        else if (ch == '#') {
            strToken += ch;
            pair<string, int> tmp(strToken, UNEQUAL);
            SYM.insert(tmp);
            _word.Kind = UNEQUAL, _word.Value = -1, _word.Name = strToken;
            Word.push_back(_word);
            cout << "< " << "UNEQUAL" << ',' << '-' << ',' << strToken << " >\n";
        }
        else if (ch == '<') {
            strToken += ch;
            ch = GetChar();
            pair<string, int> tmp;
            if (ch == '=')
            {
                strToken += ch;
                pair<string, int> tmp(strToken, EQUAL_LESS);
                SYM.insert(tmp);
                _word.Kind = EQUAL_LESS, _word.Value = -1, _word.Name = strToken;
                Word.push_back(_word);
                cout << "< " << "EQUAL_LESS" << ',' << '-' << ',' << strToken << " >\n";
            }
            else {
                ReSet();
                pair<string, int> tmp(strToken, LESS);
                SYM.insert(tmp);
                _word.Kind = LESS , _word.Value = -1, _word.Name = strToken;
                Word.push_back(_word);
                cout << "< " << "LESS" << ',' << '-' << ',' << strToken << " >\n";
            }
        }
        else if (ch == '>') {
            strToken += ch;
            ch = GetChar();
            if (ch == '=')
            {
                strToken += ch;
                pair<string, int> tmp(strToken, EQUAL_GREATER);
                SYM.insert(tmp);
                _word.Kind = EQUAL_GREATER, _word.Value = -1, _word.Name = strToken;
                Word.push_back(_word);
                cout << "< " << "EQUAL_GREATER" << ',' << '-' << ',' << strToken << " >\n";
            }
            else {
                ReSet();
                pair<string, int> tmp(strToken, GREATER);
                SYM.insert(tmp);
                _word.Kind = GREATER, _word.Value = -1, _word.Name = strToken;
                Word.push_back(_word);
                cout << "< " << "GREATER" << ',' << '-' << ',' << strToken << " >\n";
            }
        }
        else if (ch == ':')
        {
            strToken += ch;
            ch = GetChar();
            strToken += ch;
            pair<string, int> tmp(strToken, ASSIGNMENT);
            SYM.insert(tmp);
            _word.Kind = ASSIGNMENT, _word.Value = -1, _word.Name = strToken;
            Word.push_back(_word);
            cout << "< " << "ASSIGNMENT" << ',' << '-' << ',' << strToken << " >\n";
        }
        else if (ch == ',') {
            strToken += ch;
            pair<string, int> tmp(strToken, SEPARATOR);
            SYM.insert(tmp);
            _word.Kind = SEPARATOR, _word.Value = -1, _word.Name = strToken;
            Word.push_back(_word);
            cout << "< " << "SEPARATOR" << ',' << '-' << ',' << strToken << " >\n";
        }
        else if (ch == ';') {
            strToken += ch;
            pair<string, int> tmp(strToken, SEPARATOR);
            SYM.insert(tmp);
            _word.Kind = SEPARATOR, _word.Value = -1, _word.Name = strToken;
            Word.push_back(_word);
            cout << "< " << "SEPARATOR" << ',' << '-' << ',' << strToken << " >\n";
        }
        else if (ch == '(') {
            strToken += ch;
            pair<string, int> tmp(strToken, LPAR);
            SYM.insert(tmp);
            _word.Kind = LPAR, _word.Value = -1, _word.Name = strToken;
            Word.push_back(_word);
            cout << "< " << "LPAR" << ',' << '-' << ',' << strToken << " >\n";
        }
        else if (ch == ')') {
            strToken += ch;
            pair<string, int> tmp(strToken, RPAR);
            SYM.insert(tmp);
            _word.Kind = RPAR, _word.Value = -1, _word.Name = strToken;
            Word.push_back(_word);
            cout << "< " << "RPAR" << ',' << '-' << ',' << strToken << " >\n";
        }
        else if (ch == '.') {
            strToken += ch;
            pair<string, int> tmp(strToken, SEPARATOR);
            SYM.insert(tmp);
            _word.Kind = SEPARATOR, _word.Value = -1, _word.Name = strToken;
            Word.push_back(_word);
            cout << "< " << "SEPARATOR" << ',' << '-' << ',' << strToken << " >\n";
        }
        else {
        cout <<"错误符号: " << ch << endl;
        }
        if (POS == Len - 1) break;
    }
}
Table_Element Find(string id)//在符号表中寻找标识符id
{
    Table_Element ans;
    ans.Kind = -1;
    for (int i = 0; i < (int)TABLE.size(); i++)
    {
        if (TABLE[i].Name == id) {
            ans = TABLE[i];
            break;
        }
    }
    return ans;
}
int Expression(int index, int Lev, int con) //表达式
{
    vector<code_data> Tmp_array;
    code_data Tmp_code;
    code_data Start;
    Start.l = 1;
    bool Next_item = false; //后续项
    bool Next_factor = false; //后续因子
    bool Plus = false;
    for (int i = 0; i < Lev * 2 + con; i++) cout << '\t';
    cout << "表达式" << endl;
    if (Word[index].Name == "+" || Word[index].Name == "-") {
        if (Word[index].Name == "-") {
            Start.f = "OPR";
            Start.l = 0;
            Start.a = Opr_NOT;
        }
        for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
        cout << Word[index++].Name << endl;
    }
Loop1:
    for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
    cout << "项" << endl;    
Loop2:
    for (int i = 0; i < Lev * 2 + con + 2; i++) cout << '\t';
    cout << "因子" << endl;
    for (int i = 0; i < Lev * 2 + con + 3; i++) cout << '\t';
    if (Word[index].Kind == IDENT) {
        //标识符
        Table_Element tmp = Find(Word[index].Name);
        if (tmp.Kind == CONSTSYM) {
            Tmp_code.f = "LIT", Tmp_code.l = 0, Tmp_code.a = tmp.Level;
        }
        else {
            Tmp_code.f = "LOD", Tmp_code.l = Lev - tmp.Level, Tmp_code.a = tmp.ADR;          
        }
        Tmp_array.push_back(Tmp_code);
        if (!Start.l) {
            Tmp_array.push_back(Start);
            Start.l = 1;
        }
        if (Next_factor)
        {
            int ind = Tmp_array.size() - 1;
            code_data temp = Tmp_array[ind];
            Tmp_array[ind] = Tmp_array[ind - 1];
            Tmp_array[ind - 1] = temp;
        }
        cout << Word[index++].Name << endl;
    }
    else if (Word[index].Kind == NUMBER) {
        //数
        Tmp_code.f = "LIT";
        Tmp_code.l = 0;
        Tmp_code.a = atoi(Word[index].Name.c_str());
        Tmp_array.push_back(Tmp_code);
        if (!Start.l) {
            Tmp_array.push_back(Start);
            Start.l = 1;
        }
        if (Next_factor)
        {
            int ind = Tmp_array.size() - 1;
            code_data temp = Tmp_array[ind];
            Tmp_array[ind] = Tmp_array[ind - 1];
            Tmp_array[ind - 1] = temp;
        }
        cout << Word[index++].Name << endl;
    }
    else { // 括号表达式
        cout << '(' << endl;
        index = Expression(index + 1, Lev, con+3);
        for (int i = 0; i < Lev * 2 + con + 3; i++) cout << '\t';
        cout << ')' << endl;
    }
    if (Word[index].Name == "*" || Word[index].Name == "/")
    {//后续因子
        Next_factor = true;
        for (int i = 0; i < Lev * 2 + con + 2; i++) cout << '\t';
        Tmp_code.f = "OPR";
        Tmp_code.l = 0;
        if (Word[index].Kind == MUL) Tmp_code.a = Opr_MUL;
        else Tmp_code.a = Opr_DIV;
        Tmp_array.push_back(Tmp_code);
        cout << Word[index++].Name << endl;
        goto Loop2;
    }
    else if (Word[index].Name == "+" || Word[index].Name == "-")
    {//后续项
        if (Next_item) {
            if (Plus) {
                Tmp_code.a = Opr_ADD;
            }
            else Tmp_code.a = Opr_SUB;
            Tmp_code.f = "OPR";
            Tmp_code.l = 0;
            Tmp_array.push_back(Tmp_code);
            Next_item = false;
        }
        Next_item = true;
        if (Word[index].Kind = PLUS) Plus = true;
        else Plus = false;
        for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
        cout << Word[index++].Name << endl;
        goto Loop1;
    }
    else {
        if (Next_item) {
            if (Plus) {
                Tmp_code.a = Opr_ADD;
            }
            else Tmp_code.a = Opr_SUB;
            Tmp_code.f = "OPR";
            Tmp_code.l = 0;
            Tmp_array.push_back(Tmp_code);
        }
        for (int i = 0; i < (int)Tmp_array.size(); i++)
        {
            Tmp_code = Tmp_array[i];
            Tmp_code.Addr = Cur_addr++;
            CODE.push_back(Tmp_code);
        }
        return index;
    }  
}
int Assign_statement(int index, int Lev, int con) //赋值语句
{
    code_data ans;
    Table_Element tmp;
    ans.f = "STO";
    for (int i = 0; i < Lev * 2 + con; i++) cout << '\t';
    cout << "赋值语句" << endl;
    for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
    cout << "标识符" << endl;
    for (int i = 0; i < Lev * 2 + con + 2; i++) cout << '\t';
    tmp = Find(Word[index].Name);
    ans.l = Lev - tmp.Level;
    ans.a = tmp.ADR;
    cout << Word[index++].Name << endl;
    for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
    cout << Word[index++].Name << endl; //:=
    index = Expression(index, Lev, con + 1);
    ans.Addr = Cur_addr++;
    CODE.push_back(ans);
    return index;
}
int Condition_statement(int index, int Lev, int con) //条件语句
{
    int _JPC_index; //记录跳转指令JPC的位置，以便后续补充跳转地址
    code_data Tmp_code;
    for (int i = 0; i < Lev * 2 + con; i++) cout << '\t';
    cout << "条件语句" << endl;
    for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
    cout << Word[index++].Name << endl; //if
    for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
    cout << "条件" << endl;
    if (Word[index].Kind == ODDSYM) {
        for (int i = 0; i < Lev * 2 + con + 2; i++) cout << '\t';
        cout << Word[index++].Name << endl;       
        index = Expression(index, Lev, con + 2);
        Tmp_code.f = "LIT", Tmp_code.l = 0, Tmp_code.a = 1, Tmp_code.Addr = Cur_addr++;
        CODE.push_back(Tmp_code);
        Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_GTR, Tmp_code.Addr = Cur_addr++;
        CODE.push_back(Tmp_code);
        Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = 0, Tmp_code.Addr = Cur_addr++;
        CODE.push_back(Tmp_code); //若此时栈顶元素小于等于1，则跳转到判断奇偶性的指令开始位置
        int Tmp_index = CODE.size() - 1;//记录JPC的索引
        int begin_addr = Cur_addr;
        Tmp_code.f = "LIT", Tmp_code.l = 0, Tmp_code.a = 2, Tmp_code.Addr = Cur_addr++;
        CODE.push_back(Tmp_code);
        Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_SUB, Tmp_code.Addr = Cur_addr++;
        CODE.push_back(Tmp_code);
        Tmp_code.f = "LIT", Tmp_code.l = 0, Tmp_code.a = 1, Tmp_code.Addr = Cur_addr++;
        CODE.push_back(Tmp_code);
        Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_LEQ, Tmp_code.Addr = Cur_addr++;
        CODE.push_back(Tmp_code);
        Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = begin_addr, Tmp_code.Addr = Cur_addr++; //循环过程直到条件表达式的值小于等于1
        CODE.push_back(Tmp_code);
        CODE[Tmp_index].a = Cur_addr;
        //判断是否等于1，即奇数
        Tmp_code.f = "LIT", Tmp_code.l = 0, Tmp_code.a = 1, Tmp_code.Addr = Cur_addr++;
        CODE.push_back(Tmp_code);
        Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_EQU, Tmp_code.Addr = Cur_addr++; 
        CODE.push_back(Tmp_code);
        Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = 0, Tmp_code.Addr = Cur_addr++;//不等于1则跳转，地址暂时留白
        CODE.push_back(Tmp_code);
        _JPC_index = CODE.size() - 1;
    }
    else {
        index = Expression(index, Lev, con + 2);
        for (int i = 0; i < Lev * 2 + con + 2; i++) cout << '\t';
        cout << "运算符" << endl;
        int Type = Word[index].Kind;
        for (int i = 0; i < Lev * 2 + con + 3; i++) cout << '\t';
        cout << Word[index++].Name << endl;
        index = Expression(index, Lev, con + 2);
        switch (Type)
        {
            case EQUAL: {
                Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_EQU, Tmp_code.Addr = Cur_addr++;
                CODE.push_back(Tmp_code);
                Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = 0, Tmp_code.Addr = Cur_addr++;
                CODE.push_back(Tmp_code);
                _JPC_index = CODE.size() - 1;
                break;
            }
            case UNEQUAL: {
                Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_NEQ, Tmp_code.Addr = Cur_addr++;
                CODE.push_back(Tmp_code);
                Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = 0, Tmp_code.Addr = Cur_addr++;
                CODE.push_back(Tmp_code);
                _JPC_index = CODE.size() - 1;
                break;
            }
            case LESS: {
                Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_LES, Tmp_code.Addr = Cur_addr++;
                CODE.push_back(Tmp_code);
                Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = 0, Tmp_code.Addr = Cur_addr++;
                CODE.push_back(Tmp_code);
                _JPC_index = CODE.size() - 1;
                break;
            }
            case EQUAL_LESS: {
                Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_LEQ, Tmp_code.Addr = Cur_addr++;
                CODE.push_back(Tmp_code);
                Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = 0, Tmp_code.Addr = Cur_addr++;
                CODE.push_back(Tmp_code);
                _JPC_index = CODE.size() - 1;
                break;
            }
            case GREATER: {
                Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_GTR, Tmp_code.Addr = Cur_addr++;
                CODE.push_back(Tmp_code);
                Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = 0, Tmp_code.Addr = Cur_addr++;
                CODE.push_back(Tmp_code);
                _JPC_index = CODE.size() - 1;
                break;
            }
            case EQUAL_GREATER: {
                Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_GEQ, Tmp_code.Addr = Cur_addr++;
                CODE.push_back(Tmp_code);
                Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = 0, Tmp_code.Addr = Cur_addr++;
                CODE.push_back(Tmp_code);
                _JPC_index = CODE.size() - 1;
                break;
            }
            default: {
                cout << "错误比较指令" << endl;
                break;
            }
        }
    }
    for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
    cout << Word[index++].Name << endl; //then
    if (Word[index].Kind == IDENT) index = Assign_statement(index, Lev, con + 1); //赋值语句
    else if (Word[index].Kind == IFSYM) index = Condition_statement(index, Lev, con + 1);//条件语句
    else if (Word[index].Kind == WHILESYM) index = Whilie_statement(index, Lev, con + 1);//当型循环语句
    else if (Word[index].Kind == CALLSYM) index = Call_statement(index, Lev, con + 1); //过程调用语句
    else if (Word[index].Kind == READSYM) index = Read_statement(index, Lev, con + 1); //读语句
    else if (Word[index].Kind == WRITESYM) index = Write_statement(index, Lev, con + 1); //写语句
    else if (Word[index].Kind == BEGINSYM) index = Begin_end(index, Lev, con + 1); //复合语句
    CODE[_JPC_index].a = Cur_addr;
    return index;
}
int Whilie_statement(int index, int Lev, int con) //当型循环语句
{
    code_data Tmp_code;
    int _JPC_index;
    int Conditon_addr;
    for (int i = 0; i < Lev * 2 + con; i++) cout << '\t';
    cout << "当型循环语句" << endl;
    for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
    cout << Word[index++].Name << endl; //while
    for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
    cout << "条件" << endl;
    if (Word[index].Kind == ODDSYM) {
        for (int i = 0; i < Lev * 2 + con + 2; i++) cout << '\t';
        cout << Word[index++].Name << endl; //odd
        Conditon_addr = Cur_addr;
        index = Expression(index, Lev, con + 2);
        Tmp_code.f = "LIT", Tmp_code.l = 0, Tmp_code.a = 1, Tmp_code.Addr = Cur_addr++;
        CODE.push_back(Tmp_code);
        Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_GTR, Tmp_code.Addr = Cur_addr++;
        CODE.push_back(Tmp_code);
        Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = 0, Tmp_code.Addr = Cur_addr++;
        CODE.push_back(Tmp_code); //若此时栈顶元素小于等于1，则跳转到判断奇偶性的指令开始位置
        int Tmp_index = CODE.size() - 1;//记录JPC的索引
        int begin_addr = Cur_addr;
        Tmp_code.f = "LIT", Tmp_code.l = 0, Tmp_code.a = 2, Tmp_code.Addr = Cur_addr++;
        CODE.push_back(Tmp_code);
        Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_SUB, Tmp_code.Addr = Cur_addr++;
        CODE.push_back(Tmp_code);
        Tmp_code.f = "LIT", Tmp_code.l = 0, Tmp_code.a = 1, Tmp_code.Addr = Cur_addr++;
        CODE.push_back(Tmp_code);
        Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_LEQ, Tmp_code.Addr = Cur_addr++;
        CODE.push_back(Tmp_code);
        Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = begin_addr, Tmp_code.Addr = Cur_addr++; //循环过程直到条件表达式的值小于等于1
        CODE.push_back(Tmp_code);
        CODE[Tmp_index].a = Cur_addr;
        //判断是否等于1，即奇数
        Tmp_code.f = "LIT", Tmp_code.l = 0, Tmp_code.a = 1, Tmp_code.Addr = Cur_addr++;
        CODE.push_back(Tmp_code);
        Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_EQU, Tmp_code.Addr = Cur_addr++;
        CODE.push_back(Tmp_code);
        Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = 0, Tmp_code.Addr = Cur_addr++;//不等于1则跳转，地址暂时留白
        CODE.push_back(Tmp_code);
        _JPC_index = CODE.size() - 1;
    }
    else {
        Conditon_addr = Cur_addr;
        index = Expression(index, Lev, con + 2);
        for (int i = 0; i < Lev * 2 + con + 2; i++) cout << '\t';
        cout << "运算符" << endl;
        int Type = Word[index].Kind;
        for (int i = 0; i < Lev * 2 + con + 3; i++) cout << '\t';
        cout << Word[index++].Name << endl;
        index = Expression(index, Lev, con + 2);
        switch (Type)
        {
        case EQUAL: {
            Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_EQU, Tmp_code.Addr = Cur_addr++;
            CODE.push_back(Tmp_code);
            Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = 0, Tmp_code.Addr = Cur_addr++;
            CODE.push_back(Tmp_code);
            _JPC_index = CODE.size() - 1;
            break;
        }
        case UNEQUAL: {
            Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_NEQ, Tmp_code.Addr = Cur_addr++;
            CODE.push_back(Tmp_code);
            Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = 0, Tmp_code.Addr = Cur_addr++;
            CODE.push_back(Tmp_code);
            _JPC_index = CODE.size() - 1;
            break;
        }
        case LESS: {
            Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_LES, Tmp_code.Addr = Cur_addr++;
            CODE.push_back(Tmp_code);
            Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = 0, Tmp_code.Addr = Cur_addr++;
            CODE.push_back(Tmp_code);
            _JPC_index = CODE.size() - 1;
            break;
        }
        case EQUAL_LESS: {
            Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_LEQ, Tmp_code.Addr = Cur_addr++;
            CODE.push_back(Tmp_code);
            Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = 0, Tmp_code.Addr = Cur_addr++;
            CODE.push_back(Tmp_code);
            _JPC_index = CODE.size() - 1;
            break;
        }
        case GREATER: {
            Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_GTR, Tmp_code.Addr = Cur_addr++;
            CODE.push_back(Tmp_code);
            Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = 0, Tmp_code.Addr = Cur_addr++;
            CODE.push_back(Tmp_code);
            _JPC_index = CODE.size() - 1;
            break;
        }
        case EQUAL_GREATER: {
            Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_GEQ, Tmp_code.Addr = Cur_addr++;
            CODE.push_back(Tmp_code);
            Tmp_code.f = "JPC", Tmp_code.l = 0, Tmp_code.a = 0, Tmp_code.Addr = Cur_addr++;
            CODE.push_back(Tmp_code);
            _JPC_index = CODE.size() - 1;
            break;
        }
        default:
            break;
        }
    }
    for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
    cout << Word[index++].Name << endl; //do
    if (Word[index].Kind == IDENT) index = Assign_statement(index, Lev, con + 1); //赋值语句
    else if (Word[index].Kind == IFSYM) index = Condition_statement(index, Lev, con + 1);//条件语句
    else if (Word[index].Kind == WHILESYM) index = Whilie_statement(index, Lev, con + 1);//当型循环语句
    else if (Word[index].Kind == CALLSYM) index = Call_statement(index, Lev, con + 1); //过程调用语句
    else if (Word[index].Kind == READSYM) index = Read_statement(index, Lev, con + 1); //读语句
    else if (Word[index].Kind == WRITESYM) index = Write_statement(index, Lev, con + 1); //写语句
    else if (Word[index].Kind == BEGINSYM) index = Begin_end(index, Lev, con + 1); //复合语句
    Tmp_code.f = "JMP", Tmp_code.l = 0, Tmp_code.a = Conditon_addr, Tmp_code.Addr = Cur_addr++;
    CODE.push_back(Tmp_code);
    CODE[_JPC_index].a = Cur_addr;
    return index;
}
int Call_statement(int index, int Lev, int con) //过程调用语句
{
    for (int i = 0; i < Lev * 2 + con; i++) cout << '\t';
    cout << "过程调用语句" << endl;
    for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
    cout << Word[index++].Name << endl; //call
    for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
    cout << "标识符" << endl;
    for (int i = 0; i < Lev * 2 + con + 2; i++) cout << '\t';
    Table_Element tmp = Find(Word[index].Name);
    code_data Tmp_code;
    Tmp_code.f = "CAL", Tmp_code.l = Lev - tmp.Level, Tmp_code.a = tmp.ADR, Tmp_code.Addr = Cur_addr++;
    CODE.push_back(Tmp_code);
    cout << Word[index++].Name << endl;
    return index;
}
int Read_statement(int index, int Lev, int con) //读语句
{
    code_data Tmp_code;
    for (int i = 0; i < Lev * 2 + con; i++) cout << '\t';
    cout << "读语句" << endl;
    for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
    cout << Word[index++].Name << endl;//read
    for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
    cout << "(标识符)" << endl;
    for (int i = 0; i < Lev * 2 + con + 2; i++) cout << '\t';
    cout << Word[index++].Name << endl;//(
Loop:
    Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_SCN, Tmp_code.Addr = Cur_addr++; //从屏幕读入
    CODE.push_back(Tmp_code);
    Table_Element tmp = Find(Word[index].Name);
    Tmp_code.f = "STO", Tmp_code.l = Lev - tmp.Level, Tmp_code.a = tmp.ADR, Tmp_code.Addr = Cur_addr++; 
    CODE.push_back(Tmp_code);
    for (int i = 0; i < Lev * 2 + con + 2; i++) cout << '\t';
    cout << Word[index++].Name << endl;
    if (Word[index].Name == ",") {
        for (int i = 0; i < Lev * 2 + con + 2; i++) cout << '\t';
        cout << Word[index++].Name << endl;
        goto Loop;
    }
    else {
        for (int i = 0; i < Lev * 2 + con + 2; i++) cout << '\t';
        cout << Word[index++].Name << endl;
    }
    return index;
}
int Write_statement(int index, int Lev, int con) //写语句
{
    code_data Tmp_code;
    for (int i = 0; i < Lev * 2 + con; i++) cout << '\t';
    cout << "写语句" << endl;
    for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
    cout << Word[index++].Name << endl;
    for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
    cout << "(表达式)" << endl;
    for (int i = 0; i < Lev * 2 + con + 2; i++) cout << '\t';
    cout << Word[index++].Name << endl;
Loop:
    index = Expression(index, Lev, con + 2);
    Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_PRT, Tmp_code.Addr = Cur_addr++; //输出到屏幕
    CODE.push_back(Tmp_code);
    Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_PNL, Tmp_code.Addr = Cur_addr++; //输出换行
    CODE.push_back(Tmp_code);
    if (Word[index].Name == ",") {
        for (int i = 0; i < Lev * 2 + con + 2; i++) cout << '\t';
        cout << Word[index++].Name << endl;
        goto Loop;
    }
    else {
        for (int i = 0; i < Lev * 2 + con + 2; i++) cout << '\t';
        cout << Word[index++].Name << endl;
    }
    return index;
}
int Begin_end(int index, int Lev, int con) //复合语句
{
    for (int i = 0; i < Lev * 2 + con; i++) cout << '\t';
    cout << "复合语句" << endl;
    for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
    cout << Word[index++].Name << endl;//Begin
    while (Word[index].Kind != ENDSYM)
    {
        if (Word[index].Name == ";") index++;
        if (Word[index].Kind == IDENT) index = Assign_statement(index, Lev, con + 1); //赋值语句
        else if (Word[index].Kind == IFSYM) index = Condition_statement(index, Lev, con + 1);//条件语句
        else if (Word[index].Kind == WHILESYM) index = Whilie_statement(index, Lev, con + 1);//当型循环语句
        else if (Word[index].Kind == CALLSYM) index = Call_statement(index, Lev, con + 1); //过程调用语句
        else if (Word[index].Kind == READSYM) index = Read_statement(index, Lev, con + 1); //读语句
        else if (Word[index].Kind == WRITESYM) index = Write_statement(index, Lev, con + 1); //写语句
        else if (Word[index].Kind == BEGINSYM) index = Begin_end(index, Lev, con + 1); //复合语句
    }
    for (int i = 0; i < Lev * 2 + con + 1; i++) cout << '\t';
    cout << Word[index++].Name << endl; //end
    return index;
}
void Block(int TX, int Lev)
{
    int Len = Word.size();
    int con = 0;
    Table_Element tmp;
    int DX[4];
    for (int i = 0; i < 4; i++) DX[i] = 3;
    cout << "语法树: \n"<<"程序" << endl;
    cout << '\t' << "分程序" << endl;
    while (con < Len)
    {
        if (Word[con].Kind == CONSTSYM)
        {//常量说明
            for (int i = 0; i < Lev*2 + 2; i++) cout << '\t';
            cout << "常量说明" << endl;
            tmp.Name = Word[++con].Name;
            con += 2;
            tmp.Level = atoi(Word[con++].Name.c_str());
            tmp.Kind = CONSTSYM;
            tmp.ADR = 0;
            TABLE.push_back(tmp);
            for (int i = 0; i < Lev*2 + 3; i++) cout << '\t';
            cout << "Const" << endl;
            for (int i = 0; i < Lev*2 + 3; i++) cout << '\t';
            cout << "常量定义" << endl;
            for (int i = 0; i < Lev*2 + 4; i++) cout << '\t';
            cout << tmp.Name << " " << Word[con - 2].Name << " " << tmp.Level << Word[con].Name;
            while (Word[con].Name == ",")
            {
                tmp.Name = Word[++con].Name;
                con += 2;
                tmp.Level = atoi(Word[con++].Name.c_str());
                tmp.Kind = CONSTSYM;
                tmp.ADR = 0;
                TABLE.push_back(tmp);
                cout << tmp.Name << " " << Word[con - 2].Name << " " << tmp.Level << Word[con].Name;
            }
            cout << endl;
        }
        else if (Word[con].Kind == VARSYM)
        {//变量说明
            for (int i = 0; i < Lev*2 + 2; i++) cout << '\t';
            cout << "变量说明" << endl;
            tmp.Name = Word[++con].Name;
            tmp.Kind = VARSYM;
            tmp.Level = Lev;
            tmp.ADR = DX[Lev]++;
            TABLE.push_back(tmp);
            con++;
            for (int i = 0; i < Lev*2 + 3; i++) cout << '\t';
            cout << "var" << endl;
            for (int i = 0; i < Lev*2 + 3; i++) cout << '\t';
            cout << "标识符" << endl;
            for (int i = 0; i < Lev*2 + 4; i++) cout << '\t';
            cout << tmp.Name << Word[con].Name;
            while (Word[con].Name == ",")
            {
                tmp.Name = Word[++con].Name;
                tmp.Kind = VARSYM;
                tmp.Level = Lev;
                tmp.ADR = DX[Lev]++;
                TABLE.push_back(tmp);
                cout << tmp.Name << Word[++con].Name;
            }
            cout << endl;
        }
        else if (Word[con].Kind == PROCEDURESYM)
        {//过程说明
            for (int i = 0; i < Lev*2 + 2; i++) cout << '\t';
            cout << "过程说明" << endl;
            tmp.Name = Word[++con].Name;
            tmp.Kind = PROCEDURESYM;
            tmp.Level = Lev;
            tmp.ADR = Cur_addr;     
            TABLE.push_back(tmp);
            for (int i = 0; i < Lev * 2 + 3; i++) cout << '\t';
            cout << "过程首部" << endl;
            for (int i = 0; i < Lev * 2 + 4; i++) cout << '\t';
            cout << "procedure" << endl;
            for (int i = 0; i < Lev * 2 + 4; i++) cout << '\t';
            cout << "标识符" << endl;
            for (int i = 0; i < Lev * 2 + 5; i++) cout << '\t';
            cout << tmp.Name << Word[++con].Name << endl;
            for (int i = 0; i < Lev * 2 + 3; i++) cout << '\t';
            cout << "分程序" << endl;    
            Lev++;
        }
        else
        {//语句处理
            code_data _code;
            _code.f = "INT";
            _code.l = 0;
            _code.a = DX[Lev];
            _code.Addr = Cur_addr++;
            CODE.push_back(_code);
            for (int i = 0; i < Lev * 2 + 2; i++) cout << '\t';
            cout << "语句" << endl;
            if (Word[con].Kind == IDENT) con = Assign_statement(con, Lev, 3); //赋值语句
            else if (Word[con].Kind == IFSYM) con = Condition_statement(con, Lev, 3);//条件语句
            else if (Word[con].Kind == WHILESYM) con = Whilie_statement(con, Lev, 3);//当型循环语句
            else if (Word[con].Kind == CALLSYM) con = Call_statement(con, Lev, 3); //过程调用语句
            else if (Word[con].Kind == READSYM) con = Read_statement(con, Lev, 3); //读语句
            else if (Word[con].Kind == WRITESYM) con = Write_statement(con, Lev, 3); //写语句
            else if (Word[con].Kind == BEGINSYM) con = Begin_end(con, Lev, 3); //复合语句
            if (con < Len && Word[con].Kind == SEPARATOR && Lev > 0) {
                Lev--;
                code_data Tmp_code;
                Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_RET, Tmp_code.Addr = Cur_addr++;
                CODE.push_back(Tmp_code);
            }
        }
        con++;
    }
    code_data Tmp_code;
    Tmp_code.f = "OPR", Tmp_code.l = 0, Tmp_code.a = Opr_RET, Tmp_code.Addr = Cur_addr++;
    CODE.push_back(Tmp_code);
}
void Print_Table()
{
    int Len = TABLE.size();
    cout << "符号表: "<< endl;
    cout << "Name" << "\t\t" << "Kind" << "\t\t" << "Level" << "\t\t" << "ADR" << endl;
    for (int i = 0; i < Len; i++)
    {
        cout << TABLE[i].Name << "\t\t" << Code_SYM[TABLE[i].Kind] << "\t\t" << TABLE[i].Level << "\t\t" << TABLE[i].ADR << endl;
    }
}
void Print_Code()
{
    int Len = CODE.size();
    cout << "目标代码:" << endl;
    cout << "Addr" << '\t' << "OP" << '\t' << "L" << '\t' << "A" << endl;
    for (int i = 0; i < Len; i++)
    {
        cout << CODE[i].Addr << '\t' << CODE[i].f << '\t' << CODE[i].l << '\t' << CODE[i].a << endl;
    }
}
int main()
{
    initKeyWord();
    InFile.open(FileName[0]);
    string tmp;
    while (getline(InFile, tmp))
    {
        IN += tmp;
        IN += '\n';
    }
    InFile.close();
    cout << IN;
    GetSym();
    Block(0, 0);
    Print_Table();
    Print_Code();
    return 0;
}

