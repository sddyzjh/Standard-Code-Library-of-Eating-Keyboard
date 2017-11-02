/// 模拟退火.
/// 可能需要魔法调参. 慎用!
/// Tbegin: 退火起始温度.
/// Tend: 退火终止温度.
/// rate: 退火比率.
/// 退火公式: rand_range(0, 1) > exp(dist / T), 其中 dist 为计算出的优化增量.
//////////////////////////////////////////////////////////////////////////
srand(11212);
db Tbegin = 1e2;
db Tend = 1e-6;
db T = Tbegin;
db rate = 0.99995;
int tcnt = 0;
point mvbase = point(0.01, 0.01);
point curp = p[1];
db curmax = GetIntArea(curp);
while(T >= Tend)
{
    // 生成一个新的解.
    point nxtp = curp + point(
        (randdb() - 0.5) * 2.0 * mvbase.x * T,
        (randdb() - 0.5) * 2.0 * mvbase.y * T);
    // 计算这个解的价值.
    db v = GetIntArea(nxtp);
    // 算出距离当前最优解有多远.
    db dist = v - curmax;
    if(dist > eps || (dist < -eps && randdb() > exp(dist / T)))
    {
        // 更新方案和答案.
        curmax = v;
        curp = nxtp;
        tcnt++;
    }
    T *= rate;
}