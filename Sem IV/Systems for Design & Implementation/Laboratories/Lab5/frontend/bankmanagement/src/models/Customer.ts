import { Account } from "./Account";

export interface Customer {
    id: number;
    name: string;
    phone: string;
    email: string;
    address: string;
    total_savings: number;
    total_loans: number;
    accounts: Account[];
}