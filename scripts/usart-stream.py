import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=0)

def main():
    with open('test.gcode') as fh:
        for line in fh:
            ser.write(line)
            print('Processing {}.'.format(line.strip()))
            while True:
                answer = ser.readline()
                if (('Motion is complete' in answer) or 
                    ('Set feedrate' in answer)):
                    break

    # input('nya')
    ser.close()


if __name__ == '__main__':
    main()
