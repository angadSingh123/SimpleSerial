using System;
using System.IO.Ports;
using System.Text;

public class SimpleSerial
{
    private const String DEFAULT_PORT = "COM8";

    private const int DEFAULT_BAUDRATE = 9600;

    private const System.IO.Ports.StopBits DEFAULT_STOPBITS = System.IO.Ports.StopBits.One;

    private const System.IO.Ports.Parity DEFAULT_PARITY = System.IO.Ports.Parity.None;

    private const int DEFAULT_DATABITS = 8;

    private const int DEFAULT_BUFFER_SIZE = 50;

    private String Port { get; set; }

    private int Baudrate { get; set; }

    private int Buffer { get; set; }

    private byte[] ReadBuffer;

    private bool Overlapped { get; set; }

    private SerialPort Serial;

    private String read;

    public int available { get; private set; }

    public event EventHandler <SimpleSerialArgs> DataReady;    

    public SimpleSerial(string port, int baudRate, bool Overlapped)
    {

        this.Port = port;

        this.Baudrate = baudRate;

        available = 0;

        Serial = new SerialPort(Port, Baudrate, DEFAULT_PARITY, DEFAULT_DATABITS, DEFAULT_STOPBITS)
        {
            ReadBufferSize = DEFAULT_BUFFER_SIZE
        };

        this.Overlapped = Overlapped;

        if (this.Overlapped) Serial.DataReceived += new SerialDataReceivedEventHandler(DataReceived);

        try
        {

            Serial.Open();

        }

        catch (Exception e)
        {

            Console.WriteLine(e.Message);
        }

    }

    private void DataReceived(object sender, EventArgs e)
    {
        available = Serial.BytesToRead;

        read = Serial.ReadLine();

        SimpleSerialArgs s = new SimpleSerialArgs();

        DataReady(this, SimpleSerialArgs.Empty);

    }

    public void SetReadBufferSize(int sz) => this.Buffer = sz;

    public int Available() {

        if (!Overlapped) return Serial.BytesToRead;

        else return available;

    }

    public string ReadString()
    {

        if (!Overlapped && Serial.BytesToRead > 0)
        {

            return Serial.ReadLine();

        }        

        else return read;

    }

    public byte[] Read()
    {

        if (!Overlapped && Serial.BytesToRead > 0)
        {

            ReadBuffer = new Byte[Serial.BytesToRead];

            Serial.Read(ReadBuffer, 0, Serial.BytesToRead);

            return ReadBuffer;
        }

        else return ReadBuffer;
    }

    public class SimpleSerialArgs : EventArgs
    {
        public new static readonly SimpleSerialArgs Empty;
    }

}




