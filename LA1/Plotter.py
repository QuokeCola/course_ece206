import matplotlib.pyplot as plt
class DataPlotter:
    def __init__(self, filename) -> None:
        self.times = []
        self.input = []
        self.output = []
        self.Filename = ''
        self.datast = ['time,input,output\n']
        super().__init__()
        self.Filename = filename
        raw_data = open(self.Filename,'r').readlines()
        data = []
        # Get rid of useless data, or format conversion.
        for i in range(0,len(raw_data)):
            strset = raw_data[i].split(' ')
            if (strset.__contains__('->') and len(strset)==4):
                strset.remove('->')
                strset[2] = strset[2].strip('\n')
                if not(strset.__contains__('Vc')):
                    data.append(strset)   
        # Initialize for time interpolation and data conversion.

        ind = 0
        ds = data[0]
        timeset = ds[0].split(':')
        starttime = float(timeset[0])*60*60+float(timeset[1])*60+float(timeset[2])
        lasttimestamp = 0

        # For write csv.
        for ds in data:
            timeset = ds[0].split(':')
            timestamp = float(timeset[0])*60*60+float(timeset[1])*60+float(timeset[2])-starttime
            # linear interpolation for time and write data to datast
            if ds[0]!=data[ind][0]:
                offset = (timestamp-lasttimestamp)/float(data.index(ds)-ind)
                for i in range(ind,data.index(ds)):
                    self.times[i] += (i-ind)*offset
                    self.datast.append(str(self.times[i])+','+str(self.input[i])+','+str(self.output[i])+'\n')
                ind = data.index(ds)
                lasttimestamp = timestamp
            # Add data to time
            self.times.append(timestamp)
            self.input.append(float(ds[1]))
            self.output.append(float(ds[2]))
    def plot(self, Duration = 5.0):
        # Select range
        endInd = max(len(self.times)-1,0)
        for i in self.times:
            if i > Duration:
                endInd = i
                break
        file = open(self.Filename+'.csv', 'w+')
        file.writelines(self.datast)
        file.close
        
        # Plot
        plt.title(self.Filename.strip('Data/'))
        plt.plot(self.times[:self.times.index(endInd)], self.input[:self.times.index(endInd)], label = 'input')
        plt.plot(self.times[:self.times.index(endInd)], self.output[:self.times.index(endInd)], label = 'output')
        plt.legend()
        plt.show()
    def find(self):
        RiseInd = []
        DownInd = []
        for i in range(0,len(self.output)):
            if (self.output[i] - 3.0) * (self.output[min(len(self.output)-1,i+1)]-3.0) < 0:
                if self.output[i] < 3.0 and self.output[min(len(self.output)-1,i+1)] >3.0:
                    RiseInd.append(i)
                else:
                    DownInd.append(i)
        Test = self.times[DownInd[1]] - self.times[RiseInd[1]]
        if Test > 0:
            switch = False
        else:
            switch = True
        HTime = 0.0
        DTime = 0.0
        count = 0
        for i in range(1,min(len(RiseInd),len(DownInd))-2):
            if switch:
                HTime += (self.times[DownInd[i]] - self.times[RiseInd[i-1]])
                DTime += (self.times[RiseInd[i]] - self.times[DownInd[i]])
            else:
                HTime += (self.times[DownInd[i]] - self.times[RiseInd[i]])
                DTime += (self.times[RiseInd[i+1]] - self.times[DownInd[i]])
            count += 1 
        dutyCycle = HTime/(HTime+DTime)
        AvgHt = HTime/count
        AvgDt = DTime/count
        AvgLt = (HTime+DTime)/count

        # print('dutyC = '+ str(dutyCycle))
        # print('AvgHt = '+ str(AvgHt))
        # print('AvgDt = '+ str(AvgDt))
        # print('AvgLt = '+ str(AvgLt))
        
        return {'dutyCycle'                 :dutyCycle, 
                'Average High Level Time'   :AvgHt, 
                'Average Low Level Time'    :AvgDt, 
                'Average Cycle Time'        :AvgLt}
Data10k_1 = DataPlotter('Data/10k_1')
Data10k_2 = DataPlotter('Data/10k_2')
Data20k_1 = DataPlotter('Data/20k_1')
Data20k_2 = DataPlotter('Data/20k_2')
Res = [Data10k_1.find(), Data10k_2.find(), Data20k_1.find(), Data20k_2.find()]
Outputres = open('Results.csv','w+')
OutputLine = []
for i in Res:
    OutputLine.append("{}, {}, {}, {}\n".format(i['dutyCycle'],i['Average High Level Time'],i['Average Low Level Time'],i['Average Cycle Time']))
    print("{}, {}, {}, {}\n".format(i['dutyCycle'],i['Average High Level Time'],i['Average Low Level Time'],i['Average Cycle Time']))
Outputres.writelines(OutputLine)
#Data.plot(2)
