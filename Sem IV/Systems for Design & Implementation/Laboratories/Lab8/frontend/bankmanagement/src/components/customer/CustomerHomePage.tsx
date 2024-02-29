import { CssBaseline, Container, Typography } from "@mui/material";
import React from "react";
import { CustomerMenu } from "./CustomerMenu";

export const CustomerHomePage = () => {

    return (
        <React.Fragment>
            <CssBaseline />

            <CustomerMenu />
            <Container maxWidth="xl">
                <Typography variant="h4" component="h4" gutterBottom>
                    Use the menu above to manage customers.
                </Typography>
            </Container>
        </React.Fragment>
    );
};