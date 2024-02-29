import { Card, CardContent, CssBaseline, IconButton } from "@mui/material";
import { Container } from "@mui/system";
import { useEffect, useState } from "react";
import { Link, useParams } from "react-router-dom";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { BACKEND_URL } from "../../utils";
import { AccountMenu } from "./AccountMenu";
import { Account } from "../../models/Account";
import React from "react";

export const AccountDetails = () => {
    const { accountId } = useParams();
    const [account, setAccount] = useState<Account>();

    useEffect(() => {
        const fetchAccount = async () => {
            const response = await fetch(`${BACKEND_URL}/account/${accountId}`);
            const account = await response.json();
            setAccount(account[0]);
        };
        fetchAccount();
    }, [accountId]);

    return (
        <React.Fragment>
            <CssBaseline />

            <AccountMenu />
            <Card>
                <CardContent>
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/account`}>
                        <ArrowBackIcon />
                    </IconButton>{" "}
                    <h3>Account Details</h3>
                    <p>Name: {account?.name}</p>
                    <p>IBAN: {account?.iban}</p>
                    <p>BIC/SWIFT: {account?.bicswift}</p>
                    <p>Balance: {account?.balance}</p>
                    <p>Currency: {account?.currency}</p>
                    <p style={{ textAlign: "left", marginLeft: "12px" }}>Customers:</p>
                </CardContent>
            </Card>
        </React.Fragment>
    );
};