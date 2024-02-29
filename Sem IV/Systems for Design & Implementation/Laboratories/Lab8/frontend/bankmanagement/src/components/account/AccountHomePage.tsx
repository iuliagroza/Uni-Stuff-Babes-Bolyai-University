import { CssBaseline, Container, Typography } from "@mui/material";
import React from "react";
import { AccountMenu } from "./AccountMenu";

export const AccountHomePage = () => {

    return (
        <React.Fragment>
            <CssBaseline />

            <AccountMenu />
            <Container maxWidth="xl">
                <Typography variant="h4" component="h4" gutterBottom>
                    Use the menu above to manage accounts.
                </Typography>
            </Container>
        </React.Fragment>
    );
};