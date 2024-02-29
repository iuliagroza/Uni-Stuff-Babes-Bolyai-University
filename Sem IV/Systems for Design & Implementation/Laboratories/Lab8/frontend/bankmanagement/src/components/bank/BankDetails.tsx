import { Card, CardContent, CssBaseline, IconButton } from "@mui/material";
import { Container } from "@mui/system";
import { useEffect, useState } from "react";
import { Link, useParams } from "react-router-dom";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { BACKEND_URL } from "../../utils";
import { BankMenu } from "./BankMenu";
import { Bank } from "../../models/Bank";
import React from "react";

export const BankDetails = () => {
    const { bankId } = useParams();
    const [bank, setBank] = useState<Bank>();

    useEffect(() => {
        const fetchBank = async () => {
            const response = await fetch(`${BACKEND_URL}/bank/${bankId}`);
            const bank = await response.json();
            setBank(bank[0]);
        };
        fetchBank();
    }, [bankId]);

    return (
        <React.Fragment>
            <CssBaseline />

            <BankMenu />
            <Card>
                <CardContent>
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/bank`}>
                        <ArrowBackIcon />
                    </IconButton>{" "}
                    <h3>Bank Details</h3>
                    <p>Name: {bank?.name}</p>
                    <p>BIC/SWIFT: {bank?.bicswift}</p>
                    <p>Headquarters: {bank?.headquarters}</p>
                    <p>Total assets: {bank?.total_assets}</p>
                    <p>Total equity: {bank?.total_equity}</p>
                    <p style={{ textAlign: "left", marginLeft: "12px" }}>Branches:</p>
                </CardContent>
            </Card>
        </React.Fragment>
    );
};