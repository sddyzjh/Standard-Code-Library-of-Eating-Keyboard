/*
    add(u,v)表示虚树上建一条边(u,,v)
*/
top=0;
s[++top]=1;
for(i=1;i<=m;i++){
    grand=lca(s[top],q[i]);
    while(1){
        if(dep[s[top-1]]<=dep[grand]){
            add(grand,s[top--]);
            if(s[top]!=grand) s[++top]=grand;
            break;
        }
        add(s[top-1],s[top]);top--;
    }
    if(s[top]!=q[i]) s[++top]=q[i];
}
while(--top>=1) add(s[top],s[top+1]); 