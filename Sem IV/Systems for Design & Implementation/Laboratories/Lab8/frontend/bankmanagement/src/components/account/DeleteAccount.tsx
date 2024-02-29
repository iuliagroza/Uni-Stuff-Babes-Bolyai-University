import axios from "axios";
import { useNavigate, useParams } from "react-router-dom";
import { BACKEND_URL } from "../../utils";
import { Button, Card, CardActions, CardContent, Container, CssBaseline, colors } from "@mui/material";
import { AccountMenu } from "./AccountMenu";
import React from "react";


export const DeleteAccount = () => {
    const { accountId } = useParams();
    const navigate = useNavigate();

    const deleteAccount = async (event: { preventDefault: () => void }) => {
        event.preventDefault();
        await axios.delete(`${BACKEND_URL}/account/${accountId}`);
        navigate("/account");
    }

    const handleCancel = (event: { preventDefault: () => void }) => {
        event.preventDefault();
        navigate("/account");
    };

    return (
        <React.Fragment>
            <CssBaseline />

            <AccountMenu />
            <Card>
                <CardContent>
                    Are you sure you want to delete this account?
                </CardContent>
                <CardActions sx={{ justifyContent: "center" }}>
                    <Button onClick={deleteAccount} variant="contained" sx={{ backgroundColor: colors.pink[500] }}>Delete</Button>
                    <Button onClick={handleCancel} variant="contained" sx={{ backgroundColor: colors.pink[500] }}>Cancel</Button>
                </CardActions>
            </Card>
        </React.Fragment>
    );
}