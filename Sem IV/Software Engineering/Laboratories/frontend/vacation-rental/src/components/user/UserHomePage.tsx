import { CssBaseline, Container, Typography } from "@mui/material";
import React from "react";
import { UserMenu } from "./UserMenu";

export const UserHomePage = () => {

    return (
        <React.Fragment>
            <CssBaseline />

            <UserMenu />
        </React.Fragment>
    );
};