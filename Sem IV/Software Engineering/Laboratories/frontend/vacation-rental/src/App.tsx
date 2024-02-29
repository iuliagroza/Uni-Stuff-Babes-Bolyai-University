import { useState } from 'react'
import './App.css'
import React from 'react'
import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import { HomePage } from './components/HomePage';
import { AdminHomePage } from './components/admin/AdminHomePage';
import { UserHomePage } from './components/user/UserHomePage';
import { ViewPublicDestinations as ViewAdminDestinations } from './components/admin/ViewPublicDestinations';
import { ViewPublicDestinations as ViewUserDestinations } from './components/user/ViewPublicDestinations';
import { ViewBucketList } from './components/user/ViewBucketList';
import LoginForm from './components/login/LoginForm';
import { AddPublicDestination as AddAdminDestination } from './components/admin/AddPublicDestination';
import { AddPublicDestination as AddUserDestination } from './components/user/AddPublicDestination';
import { AddPrivateDestination } from './components/user/AddPrivateDestination';

function App() {
  const [count, setCount] = useState(0)

  return (
    <React.Fragment>
      <Router>
        <Routes>
          <Route path="/login" element={<LoginForm />} />

          <Route path="/" element={<UserHomePage />} />
          <Route path="/public-dest/view" element={<ViewUserDestinations />} />
          <Route path="/bucket-list/view" element={<ViewBucketList />} />
          <Route path="/bucket-list/add" element={<AddPrivateDestination />} />
          <Route path="/bucket-list/add/:destinationId" element={<AddUserDestination />} />

          <Route path="/admin" element={<AdminHomePage />} />
          <Route path="/admin/public-dest/view" element={<ViewAdminDestinations />} />
          <Route path="/admin/public-dest/add" element={<AddAdminDestination />} />
        </Routes>
      </Router>

    </React.Fragment>
  )
}

export default App