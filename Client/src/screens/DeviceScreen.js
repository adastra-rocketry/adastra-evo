import React from 'react';
import { BottomNavigationAction, BottomNavigation} from '@material-ui/core';
import RestoreIcon from '@material-ui/icons/Restore';
import FavoriteIcon from '@material-ui/icons/Favorite';
import LocationOnIcon from '@material-ui/icons/LocationOn';

class DeviceScreen extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      activeTab: "status"
    };
  }

  render() {
    let {activeTab} = this.state;
    return (  
      <BottomNavigation
        value={activeTab}
        onChange={(event, newValue) => {
          this.setState({activeTab: newValue})
        }}
        showLabels
      >
        <BottomNavigationAction label="Recents" icon={<RestoreIcon />} />
        <BottomNavigationAction label="Favorites" icon={<FavoriteIcon />} />
        <BottomNavigationAction label="Nearby" icon={<LocationOnIcon />} />
      </BottomNavigation>
    );
  }
}

export default DeviceScreen;
