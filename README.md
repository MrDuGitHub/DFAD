# DFAD
。。。
1. ssh远程连接(10.0.0.11-13,10.0.0.21-23,10.0.0.31-33,10.0.0.61-73)
```Bash
 ssh -p 11 embed11@101.76.222.115
 (ssh embed12@10.0.0.12)
```
2. 建立正常流量
```Bash
 cd DDoS
 sudo tcpreplay -i eno1 10.0.0.11_ping.pcap
 sudo tcpreplay -i eno1 10.0.0.11.pcap
```
3.监测
```Bash
cd DFAD
make
./main -c 128983238761 -t 5
```
4. 异常流量
```Bash
cd DDoS/DDoS
cd 1-3 #选择实验对应的文件夹
sudo tcpreplay -i eno1 --loop=2 --pps=900 11-123.pcap
#发送本机IP所对应的pcap文件，如10.0.0.11对应11-×××.pcap
#一个攻击者 10.0.0.11
#四个攻击者 10.0.0.11 10.0.0.21 10.0.0.31 10.0.0.12
#七个攻击者 10.0.0.11/12/13   10.0.0.21/22   10.0.0.31/32
#受害者为10.0.0.61～10.0.0.65
#pps等于300×受害者数目 循环次数可分别设置为1，2，4
```
5. 提取数据并画图
```Bash
cd DFAD
cd utils
python Extract.py 
python Draw.py
```
