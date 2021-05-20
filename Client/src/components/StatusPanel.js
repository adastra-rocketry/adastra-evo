import { DataGrid } from "@material-ui/data-grid";
import React from "react";

const columns = [
  { field: "measurement", headerName: "Measurement", width: "100" },
  { field: "value", headerName: "Value", width: "400" },
];

class StatusPanel extends React.Component {
  render() {
    const { status } = this.props;
    const data = [];
    for (let varName in status) {
      data.push({
        measurement: varName,
        value: status[varName],
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
      </div>
    );
  }
}

export default StatusPanel;
