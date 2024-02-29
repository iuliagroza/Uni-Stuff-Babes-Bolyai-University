import { useState } from 'react'
import './App.css'
import React from 'react'
import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import { AppMenu } from './components/AppMenu';
import { CustomerHomePage } from './components/customer/CustomerHomePage';
import { DisplayCustomerList } from './components/customer/DisplayCustomerList';
import { UpdateCustomer } from './components/customer/UpdateCustomer';
import { AddCustomer } from './components/customer/AddCustomer';
import { DeleteCustomer } from './components/customer/DeleteCustomer';
import { CustomerBalance } from './components/customer/TotalBalanceReport';
import { CustomerDetails } from './components/customer/CustomerDetails';
import { AccountHomePage } from './components/account/AccountHomePage';
import { DisplayAccountList } from './components/account/DisplayAccountList';
import { UpdateAccount } from './components/account/UpdateAccount';
import { AddAccount } from './components/account/AddAccount';
import { DeleteAccount } from './components/account/DeleteAccount';
import { AccountDetails } from './components/account/AccountDetails';
import { BranchHomePage } from './components/branch/BranchHomePage';
import { DisplayBranchList } from './components/branch/DisplayBranchList';
import { UpdateBranch } from './components/branch/UpdateBranch';
import { AddBranch } from './components/branch/AddBranch';
import { DeleteBranch } from './components/branch/DeleteBranch';
import { BranchDetails } from './components/branch/BranchDetails';
import { BankHomePage } from './components/bank/BankHomePage';
import { DisplayBankList } from './components/bank/DisplayBankList';
import { UpdateBank } from './components/bank/UpdateBank';
import { AddBank } from './components/bank/AddBank';
import { DeleteBank } from './components/bank/DeleteBank';
import { BankDetails } from './components/bank/BankDetails';
import { ShowUserProfile } from './components/user/ShowUserProfile';

function App() {
  const [count, setCount] = useState(0)

  return (
    <React.Fragment>
      <Router>
        <Routes>
          <Route path="/" element={<AppMenu />} />

          <Route path="/bank-management" element={<BankHomePage />} />
          <Route path="/bank" element={<DisplayBankList />} />
          <Route path="/bank/add" element={<AddBank />} />
          <Route path="/bank/:bankId/delete" element={<DeleteBank />} />
          <Route path="/bank/:bankId/update" element={<UpdateBank />} />
          <Route path='/bank/:bankId/details' element={<BankDetails />} />

          <Route path="/branch-management" element={<BranchHomePage />} />
          <Route path="/branch" element={<DisplayBranchList />} />
          <Route path="/branch/add" element={<AddBranch />} />
          <Route path="/branch/:branchId/delete" element={<DeleteBranch />} />
          <Route path="/branch/:branchId/update" element={<UpdateBranch />} />
          <Route path='/branch/:branchId/details' element={<BranchDetails />} />

          <Route path="/account-management" element={<AccountHomePage />} />
          <Route path="/account" element={<DisplayAccountList />} />
          <Route path="/account/add" element={<AddAccount />} />
          <Route path="/account/:accountId/delete" element={<DeleteAccount />} />
          <Route path="/account/:accountId/update" element={<UpdateAccount />} />
          <Route path='/account/:accountId/details' element={<AccountDetails />} />

          <Route path="/customer-management" element={<CustomerHomePage />} />
          <Route path="/customer" element={<DisplayCustomerList />} />
          <Route path="/customer/add" element={<AddCustomer />} />
          <Route path="/customer/:customerId/delete" element={<DeleteCustomer />} />
          <Route path="/customer/:customerId/update" element={<UpdateCustomer />} />
          <Route path='/customer/by-total-balance' element={<CustomerBalance />} />
          <Route path='/customer/:customerId/details' element={<CustomerDetails />} />

          <Route path="/userprofile/:userId" element={<ShowUserProfile />} />
        </Routes>
      </Router>

    </React.Fragment>
  )
}

export default App