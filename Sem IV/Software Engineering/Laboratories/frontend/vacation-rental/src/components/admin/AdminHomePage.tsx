import { CssBaseline, Container, Typography } from "@mui/material";
import React from "react";
import { AdminMenu } from "./AdminMenu";

export const AdminHomePage = () => {

    return (
        <React.Fragment>
            <CssBaseline />

            <AdminMenu />
        </React.Fragment>
    );
};