import axios from "axios";
import { useNavigate, useParams } from "react-router-dom";
import { BACKEND_URL } from "../../utils";
import { Button, Card, CardActions, CardContent, Container, CssBaseline, colors } from "@mui/material";
import { BranchMenu } from "./BranchMenu";
import React from "react";


export const DeleteBranch = () => {
    const { branchId } = useParams();
    const navigate = useNavigate();

    const deleteBranch = async (event: { preventDefault: () => void }) => {
        event.preventDefault();
        await axios.delete(`${BACKEND_URL}/branch/${branchId}`);
        navigate("/branch");
    }

    const handleCancel = (event: { preventDefault: () => void }) => {
        event.preventDefault();
        navigate("/branch");
    };

    return (
        <React.Fragment>
            <CssBaseline />

            <BranchMenu />
            <Card>
                <CardContent>
                    Are you sure you want to delete this branch?
                </CardContent>
                <CardActions sx={{ justifyContent: "center" }}>
                    <Button onClick={deleteBranch} variant="contained" sx={{ backgroundColor: colors.pink[500] }}>Delete</Button>
                    <Button onClick={handleCancel} variant="contained" sx={{ backgroundColor: colors.pink[500] }}>Cancel</Button>
                </CardActions>
            </Card>
        </React.Fragment>
    );
}