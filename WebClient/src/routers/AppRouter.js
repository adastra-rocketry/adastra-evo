import React from 'react';
import { Router, Switch } from 'react-router-dom';
import { createBrowserHistory } from 'history';
import PrivateRoute from './PrivateRoute';
import PublicRoute from './PublicRoute';
import DeviceSelector from '../screens/DeviceSelector';
import DeviceScreen from '../screens/DeviceScreen';

export const history = createBrowserHistory();

/**
 * We switched from BrowserRouter to Router because we need access
 * to history (above). history is used by BrowserRouter but doesn't
 * expose it so we switched. This is all for auth so we can route users
 */

const AppRouter = () => (
  <Router history={history}>
    <div>
      <Switch>
        <PublicRoute path="/" component={DeviceSelector} exact={true} />
        <PrivateRoute path="/app" component={DeviceScreen} />
      </Switch>
    </div>
  </Router>
);

export default AppRouter;
