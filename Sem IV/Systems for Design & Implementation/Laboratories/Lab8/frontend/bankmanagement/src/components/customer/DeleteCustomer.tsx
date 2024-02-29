import axios from "axios";
import { useNavigate, useParams } from "react-router-dom";
import { BACKEND_URL } from "../../utils";
import { Button, Card, CardActions, CardContent, Container, CssBaseline, colors } from "@mui/material";
import { CustomerMenu } from "./CustomerMenu";
import React from "react";


export const DeleteCustomer = () => {
    const { customerId } = useParams();
    const navigate = useNavigate();

    const deleteCustomer = async (event: { preventDefault: () => void }) => {
        event.preventDefault();
        await axios.delete(`${BACKEND_URL}/customer/${customerId}`);
        navigate("/customer");
    }

    const handleCancel = (event: { preventDefault: () => void }) => {
        event.preventDefault();
        navigate("/customer");
    };

    return (
        <React.Fragment>
            <CssBaseline />

            <CustomerMenu />
            <Card>
                <CardContent>
                    Are you sure you want to delete all the info about the selected customer?
                </CardContent>
                <CardActions sx={{ justifyContent: "center" }}>
                    <Button onClick={deleteCustomer} variant="contained" sx={{ backgroundColor: colors.pink[500] }}>Delete customer</Button>
                    <Button onClick={handleCancel} variant="contained" sx={{ backgroundColor: colors.pink[500] }}>Cancel</Button>
                </CardActions>
            </Card>

        </React.Fragment>
    );
}