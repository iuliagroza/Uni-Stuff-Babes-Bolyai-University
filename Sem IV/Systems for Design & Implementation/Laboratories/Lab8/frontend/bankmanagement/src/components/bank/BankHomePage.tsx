import { CssBaseline, Container, Typography } from "@mui/material";
import React from "react";
import { BankMenu } from "./BankMenu";

export const BankHomePage = () => {

    return (
        <React.Fragment>
            <CssBaseline />

            <BankMenu />
            <Container maxWidth="xl">
                <Typography variant="h4" component="h4" gutterBottom>
                    Use the menu above to manage banks.
                </Typography>
            </Container>
        </React.Fragment>
    );
};