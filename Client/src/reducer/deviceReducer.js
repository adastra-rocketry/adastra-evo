import { combineReducers } from 'redux';
import {GET_DEVICE_SUCCESS, BACK_TO_DEVICE_SELECTION} from '../actionConstants/devices';

function deviceReducers(state={ selected: null }, action) {
    switch(action.type) {
      case GET_DEVICE_SUCCESS:
        const { device } = action;
        state.selected = device;
        return state;
      case BACK_TO_DEVICE_SELECTION:
        state.selected = null;
        return state;
      default:
        return state;
    }
  }



export default deviceReducers;