import { combineReducers } from 'redux';
import deviceReducer from './deviceReducer.js';

const reducer = combineReducers({
    device: deviceReducer,
});

export default reducer;