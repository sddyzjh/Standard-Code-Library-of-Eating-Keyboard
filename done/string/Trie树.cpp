#define CHAR_SIZE 26        //字符种类数
#define MAX_NODE_SIZE 10000    //最大节点数

inline int getCharID(char a) {  //返回a在子数组中的编号
    return a - 'a';
}

struct Trie
{
    int num;//记录多少单词途径该节点，即多少单词拥有以该节点为末尾的前缀
    bool terminal;//若terminal==true，该节点没有后续节点
    int count;//记录单词的出现次数，此节点即一个完整单词的末尾字母
    struct Trie *son[CHAR_SIZE];//后续节点
};

struct Trie trie_arr[MAX_NODE_SIZE];
int trie_arr_point=0;

Trie *NewTrie()
{
    Trie *temp=&trie_arr[trie_arr_point++];
    temp->num=1;
    temp->terminal=false;
    temp->count=0;
    for(int i=0;i<sonnum;++i)temp->son[i]=NULL;
    return temp;
}

//插入新词,root:树根,s:新词,len:新词长度
void Insert(Trie *root,char *s,int len)
{
    Trie *temp=root;
    for(int i=0;i<len;++i)
        {
            if(temp->son[getCharID(s[i])]==NULL)temp->son[getCharID(s[i])]=NewTrie();
            else {temp->son[getCharID(s[i])]->num++;temp->terminal=false;}
            temp=temp->son[getCharID(s[i])];
        }
    temp->terminal=true;
    temp->count++;
}
//删除整棵树
void Delete()
{
    memset(trie_arr,0,trie_arr_point*sizeof(Trie));
    trie_arr_point=0;
}
//查找单词在字典树中的末尾节点.root:树根,s:单词,len:单词长度
Trie* Find(Trie *root,char *s,int len)
{
    Trie *temp=root;
    for(int i=0;i<len;++i)
    if(temp->son[getCharID(s[i])]!=NULL)temp=temp->son[getCharID(s[i])];
    else return NULL;
    return temp;
}