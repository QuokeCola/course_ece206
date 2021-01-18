import matplotlib.pyplot as plt
class DataPlotter:
    times = []
    input = []
    output = []
    Filename = ''
    datast = ['time,input,output\n']
    def __init__(self, filename) -> None:
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
        plt.plot(self.times[:self.times.index(endInd)], self.input[:self.times.index(endInd)], label = 'input')
        plt.plot(self.times[:self.times.index(endInd)], self.output[:self.times.index(endInd)], label = 'output')
        plt.legend()
        plt.show()

Data = DataPlotter('Data/10k_2')
Data.plot()