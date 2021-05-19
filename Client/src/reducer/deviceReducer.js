import { combineReducers } from 'redux';

function deviceReducers(state={ selected: null }, action) {
    switch(action.type) {
      case "GET_DEVICES_SUCCESS":
        const { devices } = action.data;
        state.devices = devices;
        return state;
      default:
        return state;
    }
  }



export default deviceReducers;