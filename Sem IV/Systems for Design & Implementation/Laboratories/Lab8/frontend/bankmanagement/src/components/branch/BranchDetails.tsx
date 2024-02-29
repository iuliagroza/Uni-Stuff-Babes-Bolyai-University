import { Card, CardContent, CssBaseline, IconButton } from "@mui/material";
import { Container } from "@mui/system";
import { useEffect, useState } from "react";
import { Link, useParams } from "react-router-dom";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { BACKEND_URL } from "../../utils";
import { BranchMenu } from "./BranchMenu";
import { Branch } from "../../models/Branch";
import React from "react";

export const BranchDetails = () => {
    const { branchId } = useParams();
    const [branch, setBranch] = useState<Branch>();

    useEffect(() => {
        const fetchBranch = async () => {
            const response = await fetch(`${BACKEND_URL}/branch/${branchId}`);
            const branch = await response.json();
            setBranch(branch[0]);
        };
        fetchBranch();
    }, [branchId]);

    return (
        <React.Fragment>
            <CssBaseline />

            <BranchMenu />
            <Card>
                <CardContent>
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/branch`}>
                        <ArrowBackIcon />
                    </IconButton>{" "}
                    <h3>Branch Details</h3>
                    <p>Name: {branch?.name}</p>
                    <p>BIC/SWIFT: {branch?.bicswift}</p>
                    <p>Address: {branch?.address}</p>
                    <p>Total assets: {branch?.total_assets}</p>
                    <p>Total equity: {branch?.total_equity}</p>
                    <p style={{ textAlign: "left", marginLeft: "12px" }}>Accounts:</p>
                </CardContent>
            </Card>
        </React.Fragment>
    );
};