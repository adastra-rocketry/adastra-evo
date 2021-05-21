import { DataGrid } from "@material-ui/data-grid";
import React from "react";
import RocketRenderer from '../components/RocketRenderer';

const columns = [
  { field: "measurement", headerName: "Measurement", width: "100" },
  { field: "value", headerName: "Value", width: "400" },
];

class StatusPanel extends React.Component {
  render() {
    const { status } = this.props;
    const plainStatus = {
      ...status.currentDeviceState_MainData_Characteristic,
      ...status.currentDeviceState_AccData_Characteristic,
      ...status.currentDeviceState_GData_Characteristic,
      ...status.currentDeviceState_MagData_Characteristic,
      ...status.currentDeviceState_IMUData_Characteristic,
      ...status.currentDeviceState_PressureData_Characteristic,
      ...status.currentDeviceState_KalmanData_Characteristic
    }
    const data = [];
    for (let varName in plainStatus) {
      data.push({
        measurement: varName,
        value: plainStatus[varName],
        id: varName
      });
    }
    return (
      <div style={{ height: 400, width: "100%" }}>
        <DataGrid
          rows={data}
          columns={columns}
          pageSize={50}
        />
        <RocketRenderer />
      </div>
    );
  }
}

export default StatusPanel;
