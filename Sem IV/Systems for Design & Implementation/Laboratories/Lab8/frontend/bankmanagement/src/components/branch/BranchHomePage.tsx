import { CssBaseline, Container, Typography } from "@mui/material";
import React from "react";
import { BranchMenu } from "./BranchMenu";

export const BranchHomePage = () => {

    return (
        <React.Fragment>
            <CssBaseline />

            <BranchMenu />
            <Container maxWidth="xl">
                <Typography variant="h4" component="h4" gutterBottom>
                    Use the menu above to manage branches.
                </Typography>
            </Container>
        </React.Fragment>
    );
};