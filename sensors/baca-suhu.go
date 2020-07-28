// reading from sensor and save it into CSV
// budi rahardjo (@rahard)
// Mon 27 Jul 2020 09:03:45 PM WIB

package main
  
import (
    "fmt"
    "time"
    "net/http"
    "io/ioutil"
)

func main() {
   currentTime := time.Now()

   // get temperature
   resp1, err := http.Get("http://192.168.2.74/temp")
   if err != nil {
      // handle error
   }
   defer resp1.Body.Close()
   temp, err := ioutil.ReadAll(resp1.Body)
   if err != nil {
      // handle error
   }


   // get humidity
   resp2, err := http.Get("http://192.168.2.74/humidity")
   if err != nil {
      // handle error
   }
   defer resp2.Body.Close()
   humidity, err := ioutil.ReadAll(resp2.Body)
   if err != nil {
      // handle error
   }


   // print all
   fmt.Println(currentTime.Format("2006-01-02 15:04:05"), ",", string(temp), ",", string(humidity))
}
