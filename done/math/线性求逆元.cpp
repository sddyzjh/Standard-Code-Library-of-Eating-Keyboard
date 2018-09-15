inv[1] = 1;
rep(i,2,n)inv[i] = (MOD-(MOD/i)) * (ll)inv[MOD%i] % MOD;
