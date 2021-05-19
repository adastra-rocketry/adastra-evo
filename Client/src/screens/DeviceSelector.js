import { Button } from '@material-ui/core';
import React from 'react';
import { connect } from 'react-redux';
import { getDevice} from '../actions/devices';


class DeviceSelector extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            activeTab: "status"
        };
        this.onSelectButtonPress = this.onSelectButtonPress.bind(this);
    }

    onSelectButtonPress() {
        this.props.openDeviceSelector();
    }

    render() {
        return (
            <>
                <h1>Welcome.</h1>
                <div>You need to select a AdAstra Evo device to continue.</div>
                <Button onClick={() => this.onSelectButtonPress()} variant="contained" color="primary">Select device</Button>
            </>
        );
    }
}

const mapStateToProps = (state) => ({
});

const mapDispatchToProps = (dispatch) => ({
    openDeviceSelector: () => dispatch(getDevice()),
});

export default connect(mapStateToProps, mapDispatchToProps)(DeviceSelector);