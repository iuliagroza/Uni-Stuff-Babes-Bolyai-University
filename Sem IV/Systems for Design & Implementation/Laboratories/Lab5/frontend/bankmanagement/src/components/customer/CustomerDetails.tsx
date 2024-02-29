import { Card, CardContent, IconButton } from "@mui/material";
import { Container } from "@mui/system";
import { useEffect, useState } from "react";
import { Link, useParams } from "react-router-dom";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { Customer } from "../../models/Customer";
import { BACKEND_URL } from "../../utils";


export const CustomerDetails = () => {
    const { customerId } = useParams();
    const [customer, setCustomer] = useState<Customer>();

    useEffect(() => {
        const fetchCustomer = async () => {
            const response = await fetch(`${BACKEND_URL}/customer/${customerId}`);
            const customer = await response.json();
            setCustomer(customer[0]);
        };
        fetchCustomer();
    }, [customerId]);

    return (
        <Container>
            <Card>
                <CardContent>
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/customer`}>
                        <ArrowBackIcon />
                    </IconButton>{" "}
                    <h3>Customer Details</h3>
                    <p>Name: {customer?.name}</p>
                    <p>Phone number: {customer?.phone}</p>
                    <p>Email address: {customer?.email}</p>
                    <p>Address: {customer?.address}</p>
                    <p>Total savings: {customer?.total_savings}</p>
                    <p>Total loans: {customer?.total_loans}</p>
                    <p style={{ textAlign: "left" }}>Accounts:</p>
                    <ul>
                        {customer?.accounts?.map((account) => (
                            <li key={account.id}>Name: {account.name}; IBAN: {account.iban}; BIC/SWIFT:{account.bicswift}, Address: {account.address}; Balance: {account.balance}; Currency: {account.currency};</li>
                        ))}
                    </ul>
                </CardContent>
            </Card>
        </Container>
    );
};