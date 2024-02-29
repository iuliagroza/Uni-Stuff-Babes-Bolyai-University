import { useState } from 'react'
import './App.css'
import React from 'react'
import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import { AppMenu } from './components/AppMenu';
import { HomePage } from './components/HomePage';
import { DisplayCustomerList } from './components/customer/DisplayCustomerList';
import { UpdateCustomer } from './components/customer/UpdateCustomer';
import { AddCustomer } from './components/customer/AddCustomer';
import { DeleteCustomer } from './components/customer/DeleteCustomer';
import { CustomerBalance } from './components/customer/TotalBalanceReport';
import { CustomerDetails } from './components/customer/CustomerDetails';

function App() {
  const [count, setCount] = useState(0)

  return (
    <React.Fragment>

      <Router>
        <AppMenu />
        <Routes>
          <Route path="/" element={<HomePage />} />
          <Route path="/customer" element={<DisplayCustomerList />} />
          <Route path="/customer/add" element={<AddCustomer />} />
          <Route path="/customer/:customerId/delete" element={<DeleteCustomer />} />
          <Route path="/customer/:customerId/update" element={<UpdateCustomer />} />
          <Route path='/customer/by-total-balance' element={<CustomerBalance />} />
          <Route path='/customer/:customerId/details' element={<CustomerDetails />} />
        </Routes>
      </Router>

    </React.Fragment>
  )
}

export default App