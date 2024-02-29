import axios from "axios";
import { useNavigate, useParams } from "react-router-dom";
import { BACKEND_URL } from "../../utils";
import { Button, Card, CardActions, CardContent, Container, CssBaseline, colors } from "@mui/material";
import { BankMenu } from "./BankMenu";
import React from "react";


export const DeleteBank = () => {
    const { bankId } = useParams();
    const navigate = useNavigate();

    const deleteBank = async (event: { preventDefault: () => void }) => {
        event.preventDefault();
        await axios.delete(`${BACKEND_URL}/bank/${bankId}`);
        navigate("/bank");
    }

    const handleCancel = (event: { preventDefault: () => void }) => {
        event.preventDefault();
        navigate("/bank");
    };

    return (
        <React.Fragment>
            <CssBaseline />

            <BankMenu />
            <Card>
                <CardContent>
                    Are you sure you want to delete this bank?
                </CardContent>
                <CardActions sx={{ justifyContent: "center" }}>
                    <Button onClick={deleteBank} variant="contained" sx={{ backgroundColor: colors.pink[500] }}>Delete</Button>
                    <Button onClick={handleCancel} variant="contained" sx={{ backgroundColor: colors.pink[500] }}>Cancel</Button>
                </CardActions>
            </Card>
        </React.Fragment>
    );
}