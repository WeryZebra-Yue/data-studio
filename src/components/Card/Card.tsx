import { useEffect, useState } from "react";
import {
  Line,
  XAxis,
  YAxis,
  Legend,
  Tooltip,
  LineChart,
  CartesianGrid,
} from "recharts";
import styles from "./Card.module.css";
import { staticData } from "../../utils/staticData";
import { iChartProps } from "../../interfaces/Chart";

function Card({ data, title, xLine, macAddress }: iChartProps) {
  useEffect(() => {
    console.log(data);
  }, [data]);
  const [innerWidth, setInnerWidth] = useState(window.innerWidth);
  window.addEventListener("resize", () => setInnerWidth(window.innerWidth));
  return (
    <div className={styles.main}>
      <div className={styles.title}>
        {title} - <span className={styles.macAddress}>{macAddress}</span>
      </div>
      {data && (
        <LineChart
          data={data}
          width={innerWidth < 600 ? 400 : 500}
          height={innerWidth < 600 ? 250 : 300}
          margin={staticData.chart.chartMargin}
        >
          <XAxis
            dataKey="name"
            style={{
              marginTop: "20px",
            }}
          />
          <Tooltip labelClassName={styles.tooltipLabel} />
          <Legend />
          <YAxis />
          <CartesianGrid stroke="#eee" strokeDasharray="5 5" />
          <Line type="monotone" dataKey={xLine} stroke="#8884d8" />
        </LineChart>
      )}
    </div>
  );
}

export default Card;
