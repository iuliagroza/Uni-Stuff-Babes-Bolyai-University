import { Card, CardContent, CssBaseline, IconButton } from "@mui/material";
import { Container } from "@mui/system";
import { useEffect, useState } from "react";
import { Link, useParams } from "react-router-dom";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { Customer } from "../../models/Customer";
import { BACKEND_URL } from "../../utils";
import { CustomerMenu } from "./CustomerMenu";
import React from "react";


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
        <React.Fragment>
            <CssBaseline />

            <CustomerMenu />
            <Card>
                <CardContent>
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/customer`}>
                        <ArrowBackIcon />
                    </IconButton>{" "}
                    <p><b>Credit risk assessment for customer {customer?.name}:</b></p>
                    <ul>
                        <li> {customer?.credit}.toFixed(3) USD</li>
                        <li><b>Interest risk:</b> {customer?.interest}.toFixed(3)% </li>
                    </ul>
                </CardContent>
            </Card>
        </React.Fragment>
    );
};