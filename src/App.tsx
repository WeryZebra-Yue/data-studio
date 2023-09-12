import Card from "./components/Card";

import styles from "./App.module.css";

import viteLogo from "./assets/Logo.svg";

import dataRepo from "./repo/data.repo";
import { useEffect, useState } from "react";

function App() {
  const [distance, setDistance] = useState([]) as any;
  const [humidity, setHumidity] = useState([]) as any;
  const [temperature, setTemperature] = useState([]) as any;

  useEffect(() => {
    const _dataRepo: any = new dataRepo();
    async function getData() {
      await _dataRepo.getReadings(
        (distance: any, temperature: any, humidity: any) => {
          console.log(distance, temperature, humidity);
          const _distance = [...distance];
          setDistance(_distance);
          const _humidity = [...humidity];
          setHumidity(_humidity);
          const _temperature = [...temperature];
          setTemperature(_temperature);
        }
      );
    }
    getData();
    return () => {
      setDistance([]);
      setHumidity([]);
      setTemperature([]);
    };
  }, []);
  useEffect(() => {
    // setDistance(distance);
    setHumidity(humidity);
    setTemperature(temperature);
  }, [distance, humidity, temperature]);
  return (
    <div>
      <div className={styles.header}>
        <img src={viteLogo} alt="Vite Logo" />
      </div>
      <div className={styles.chartsContainer}>
        <div className={styles.charts}>
          <Card
            data={distance}
            xLine="distance"
            title="Distance Sensor"
            macAddress="00:1B:63:84:45:E6"
          />
          <Card
            data={temperature}
            xLine="temperature"
            title="Temperature Sensor"
            macAddress="00:1B:63:84:45:E6"
          />{" "}
        </div>
        <div className={styles.charts}>
          <Card
            data={humidity}
            xLine="humidity"
            title="Humidity Sensor"
            macAddress="00:1B:63:84:45:E6"
          />{" "}
          <Card data={[]} xLine="humidity" title="-" macAddress="-" />{" "}
        </div>
      </div>
    </div>
  );
}

export default App;
