#!/usr/bin/env python
from matplotlib import pyplot as plt
import numpy as np
import sys


color = ['b', 'g', 'r', 'c', 'm', 'y', 'k', '#9400D3', '#FF8C00', '#FA8072']


def plotOutput(file_name):
    c1 = 0
    c2 = 0
    data = []
    cols = []
    col_n = 0
    with open(file_name, 'r') as l:
        first_line = l.readline()
        cols = first_line.split(",")
        col_n = len(cols) - 1



    f, grph = plt.subplots(6, sharex=True)
    grph[0].set_title('Link Rates')
    grph[1].set_title('Buffer Occupancy')
    grph[2].set_title('Packet Loss')
    grph[3].set_title('Flow Rate')
    grph[4].set_title('Window Size')
    grph[5].set_title('Packet Delay')

    x = np.loadtxt(file_name, unpack=True, delimiter = ',', usecols = (0,))

    for i in xrange(1, col_n, 4):
        if 'L' in cols[i] or 'F' in cols[i]:
            y1, y2, y3 = np.loadtxt(file_name, unpack=True, delimiter = ',', usecols=(i + 1, i + 2, i + 3))


            if 'L' in cols[i]:
                grph[0].plot(x, y1, color[c1], label = cols[i])
                grph[1].plot(x, y2, color[c1], label = cols[i])
                grph[2].plot(x, y3, color[c1], label = cols[i])
                c1 += 1
            else:
                grph[3].plot(x, y1, color[c2], label = cols[i])
                grph[4].plot(x, y2, color[c2], label = cols[i])
                grph[5].plot(x, y3, color[c2], label = cols[i])
                c2 += 1


        else:
            break


    grph[0].legend(prop={'size':3})
    grph[1].legend(prop={'size':3})
    grph[2].legend(prop={'size':3})
    grph[3].legend(prop={'size':3})
    grph[4].legend(prop={'size':3})
    grph[5].legend(prop={'size':3})
    plt.show()


def plotOutputArg(file_name, arg):


    c1 = 0
    argl = len(arg)
    data = []
    cols = []
    col_n = 0
    with open(file_name, 'r') as l:
        first_line = l.readline()
        cols = first_line.split(",")
        col_n = len(cols) - 1



    if 'L' in arg[0]:

        f, grph = plt.subplots(3, sharex=True)
        grph[0].set_title('Buffer Occupancy')
        grph[1].set_title('Packet Loss')
        grph[2].set_title('Link Rate')

        x = np.loadtxt(file_name, unpack=True, delimiter = ',', usecols = (0,))

        for i in xrange(1, col_n, 4):
            if cols[i] in  arg:
                y1, y2, y3 = np.loadtxt(file_name, unpack=True, delimiter = ',', usecols=(i + 1, i + 2, i + 3))



                grph[0].plot(x, y1, color[c1], label = cols[i])
                grph[1].plot(x, y2, color[c1], label = cols[i])
                grph[2].plot(x, y3, color[c1], label = cols[i])
                c1 += 1


            if c1 == argl:
                break

        grph[0].legend(prop={'size':8})
        grph[0].set_ylabel('KB', fontsize = 8)

        grph[1].legend(prop={'size':8})
        grph[1].set_ylabel('packets per second', fontsize = 8)

        grph[2].legend(prop={'size':8})
        grph[2].set_ylabel('Megabits per second (Mbps)', fontsize = 8)
        grph[2].set_xlabel('time (s)')


        plt.show()


    elif 'F' in arg[0]:

        f, grph = plt.subplots(4, sharex=True)
        startFindex = 1
        grph[0].set_title('Flow Send Rate')
        grph[1].set_title('Flow Receive Rate')
        grph[2].set_title('Packet Delay')
        grph[3].set_title('Window Size')

        x = np.loadtxt(file_name, unpack=True, delimiter = ',', usecols = (0,))

        for i in xrange(1, col_n, 4):

            if 'F' in cols[i]:
                startFindex = i
                break


        for i in xrange(startFindex, col_n, 5):

            if cols[i] in  arg:

                y1, y2, y3, y4 = np.genfromtxt(file_name, unpack=True, delimiter = ',', usecols=(i + 1, i + 2, i + 3, i + 4))



                grph[0].plot(x, y1, color[c1], label = cols[i])
                grph[1].plot(x, y2, color[c1], label = cols[i])
                grph[2].plot(x, y3, color[c1], label = cols[i])
                grph[3].plot(x, y4, color[c1], label = cols[i])
                c1 += 1


            if c1 == argl:
                break

        grph[0].legend(prop={'size':8})
        grph[0].set_ylabel('Megabits per second (Mbps)', fontsize = 7)

        grph[1].legend(prop={'size':8})
        grph[1].set_ylabel('Megabits per second (Mbps)', fontsize = 7)

        grph[2].legend(prop={'size':8})
        grph[2].set_ylabel('milliseconds', fontsize = 7)

        grph[3].legend(prop={'size':8})
        grph[3].set_ylabel('size', fontsize = 7)

        grph[3].set_xlabel('time (s)')
        plt.show()

    else:

        startHindex = 1
        f, grph = plt.subplots(2, sharex=True)
        grph[0].set_title('Send Rate')
        grph[1].set_title('Receive Rate')

        x = np.loadtxt(file_name, unpack=True, delimiter = ',', usecols = (0,))
        for i in xrange(1, col_n, 4):
            if 'F' in cols[i]:
                startHindex = i
                break
        for i in xrange(startHindex, col_n, 5):
            if cols[i] in arg:
                startHindex = i
                break

        for i in xrange(startHindex, col_n, 3):
            if cols[i] in  arg:
                y1, y2 = np.loadtxt(file_name, unpack=True, delimiter = ',', usecols=(i + 1, i + 2))



                grph[0].plot(x, y1, color[c1], label = cols[i])
                grph[1].plot(x, y2, color[c1], label = cols[i])
                c1 += 1


            if c1 == argl:
                break

        grph[0].legend(prop={'size':8})
        grph[0].set_ylabel('Megabits per second (Mbps)', fontsize = 8)

        grph[1].legend(prop={'size':8})
        grph[1].set_ylabel('Megabits per second (Mbps)', fontsize = 8)
        grph[1].set_xlabel('time (s)')



        plt.show()


filename = sys.argv[1]
arguments = sys.argv[2:]
plotOutputArg(filename, arguments)
