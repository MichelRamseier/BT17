配置config.ini文件时，必须保证thread[N].devcie[M]中，N,M是连续的。
比如：
thread[0].devcie[0]
thread[0].devcie[1]
thread[0].devcie[3]
demo只读取到thread[0].devcie[1]的配置，由于缺少thread[0].devcie[2]，
thread[0].devcie[3]和其之后的配置都会被忽略。