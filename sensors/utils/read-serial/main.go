package main

import "fmt"
import "log"
import "time"
import "github.com/tarm/serial"

func main() {
        config := &serial.Config{
                Name: "/dev/cu.usbserial-10",
                Baud: 9600,
                ReadTimeout: 1,
                Size: 8,
        }

        stream, err := serial.OpenPort(config)
        if err != nil {
                log.Fatal(err)
        }

        buf := make([]byte, 1024)

        for {
                n, err := stream.Read(buf)
                if err != nil {
                        log.Println(err)
                        time.Sleep(1 * time.Second)
                }
                s := string(buf[:n])
                fmt.Println(s)
        }
}

