import {
  ref,
  onValue,
  Database,
  getDatabase,
  DataSnapshot,
} from "firebase/database";
import { firebaseConfig } from "../utils/staticData";
import { FirebaseApp, initializeApp } from "firebase/app";
import { IDistance } from "../interfaces/Schema";

class dataRepo {
  db: Database;
  app: FirebaseApp;
  humidity: any[] = [];
  temperature: any[] = [];
  distance: IDistance[] = [];
  constructor() {
    this.app = initializeApp(firebaseConfig);
    this.db = getDatabase(this.app);
  }
  getReadings = async (cb: any) => {
    onValue(ref(this.db, "readings/"), (snapshot: DataSnapshot) => {
      const data = snapshot.val();
      console.log(data);
      if (
        new Date(
          parseInt(this.distance[this.distance.length - 1]?.name)
        ).toLocaleTimeString() !== data["Distance Sensor"]["time"]
      )
        this.distance.push({
          name: new Date(
            new Date(
              new Date(parseInt(data["Distance Sensor"]["time"])).setHours(
                new Date().getHours() + 1
              )
            ).setMinutes(new Date().getMinutes())
          )
            .toLocaleTimeString()
            .slice(3, 5),
          distance: parseFloat(data["Distance Sensor"]["distance"]),
        });
      if (
        new Date(
          parseInt(this.distance[this.distance.length - 1]?.name)
        ).toLocaleTimeString() !== data["Temperature Sensor"]["time"]
      ) {
        this.temperature.push({
          name: new Date(
            new Date(
              new Date(parseInt(data["Distance Sensor"]["time"])).setHours(
                new Date().getHours() + 1
              )
            ).setMinutes(new Date().getMinutes())
          )
            .toLocaleTimeString()
            .slice(3, 5),

          temperature: parseFloat(data["Temperature Sensor"]["temperature"]),
        });
        this.humidity.push({
          name: new Date(
            new Date(
              new Date(parseInt(data["Temperature Sensor"]["time"])).setHours(
                new Date().getHours() + 1
              )
            ).setMinutes(new Date().getMinutes())
          )
            .toLocaleTimeString()
            .slice(3, 5),
          humidity: parseFloat(data["Temperature Sensor"]["humidity"]),
        });
      }
      cb(this.distance, this.temperature, this.humidity);
    });
  };
}
export default dataRepo;
