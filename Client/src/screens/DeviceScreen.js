import React from "react";
import { BottomNavigationAction, BottomNavigation } from "@material-ui/core";
import RestoreIcon from "@material-ui/icons/Restore";
import FavoriteIcon from "@material-ui/icons/Favorite";
import LocationOnIcon from "@material-ui/icons/LocationOn";
import TabPanel from "../components/TabPanel";
import StatusPanel from "../components/StatusPanel";
import { connect } from "react-redux";
import { enableLiveDataSubscription } from "../actions/devices";

class DeviceScreen extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      activeTab: 0,
    };
    props.enableLiveDataSubscription();
  }
  

  shouldComponentUpdate() {
    return true;
  }

  render() {
    let { activeTab } = this.state;
    let { deviceStatus } = this.props;
    return (
      <>
        <TabPanel value={activeTab} index={0}>
          <StatusPanel status={deviceStatus} />
        </TabPanel>
        <TabPanel value={activeTab} index={1}>
          Item Two
        </TabPanel>
        <TabPanel value={activeTab} index={2}>
          Item Three
        </TabPanel>

        <BottomNavigation
          value={activeTab}
          onChange={(event, newValue) => {
            this.setState({ activeTab: newValue });
          }}
          style={{}}
          showLabels
        >
          <BottomNavigationAction label="Recents" icon={<RestoreIcon />} />
          <BottomNavigationAction label="Favorites" icon={<FavoriteIcon />} />
          <BottomNavigationAction label="Nearby" icon={<LocationOnIcon />} />
        </BottomNavigation>
      </>
    );
  }
}

const mapStateToProps = (state) => ({
  deviceStatus: state.device.currentDeviceState,
});

const mapDispatchToProps = (dispatch) => ({
  enableLiveDataSubscription: () => dispatch(enableLiveDataSubscription()),
});

export default connect(mapStateToProps, mapDispatchToProps)(DeviceScreen);
