import matplotlib.pyplot as plt
import csv
 
EPOCHS = []
PREYPOPS = []
PREDPOPS = []

with open('./data.dat', 'r') as datafile:
  plotting = csv.reader(datafile, delimiter=' ')
     
  for ROWS in plotting:
    EPOCHS.append(int(ROWS[2]))
    PREYPOPS.append(int(ROWS[1]))
    PREDPOPS.append(int(ROWS[0]))
 
plt.plot(EPOCHS, PREYPOPS)
plt.plot(EPOCHS, PREDPOPS)
plt.title('plot')
plt.xlabel('EPOCH')
plt.ylabel('POPULATION')
plt.show()
