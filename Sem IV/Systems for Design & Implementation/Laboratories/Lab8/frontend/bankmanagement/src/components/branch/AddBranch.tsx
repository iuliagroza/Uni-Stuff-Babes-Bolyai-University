import { Link, useNavigate, useParams } from "react-router-dom";
import { useState } from "react";
import { BACKEND_URL } from "../../utils";
import { Button, Card, CardContent, Container, IconButton, TextField, FormLabel, colors, Autocomplete, CssBaseline } from "@mui/material";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { useForm } from "react-hook-form";
import { BranchMenu } from "./BranchMenu";
import { Branch } from "../../models/Branch";
import React from "react";


export const AddBranch = () => {
    const { branchId } = useParams<{ branchId: string }>();
    const navigate = useNavigate();
    const [loading, setLoading] = useState(false);

    const [branch, setBranch] = useState<Branch>({
        id: parseInt(String(branchId)),
        name: "",
        bicswift: "",
        address: "",
        total_assets: 0,
        total_equity: 0,
    });

    const [validName, setValidName] = useState(true);

    const handleNameChange = (event: React.ChangeEvent<HTMLInputElement>) => {
        const name = event.target.value;
        setBranch({ ...branch, name: name });
        setValidName(name.length >= 5);
    };

    const addBranch = async (event: { preventDefault: () => void }) => {
        event.preventDefault();
        setLoading(true);
        fetch(`${BACKEND_URL}/branch`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(branch)
        }).then(response => {
            if (response.ok) {
                alert("Branch added successfully");
            } else {
                console.error('Error adding branch:', response.statusText);
                alert("Error adding branch: " + response.statusText);
            }
            navigate(`/branch`);
            setLoading(false);
        }).catch(error => {
            console.error('Error adding branch:', error);
            setLoading(false);
        });
    }

    return (
        <React.Fragment>
            <CssBaseline />

            <BranchMenu />
            <Card>
                <CardContent>
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/branch`}>
                        <ArrowBackIcon />
                    </IconButton>{" "}
                    <form onSubmit={addBranch} style={{ display: "flex", flexDirection: "column", padding: "8px" }}>
                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Name
                            </FormLabel>
                            <TextField
                                id="name"
                                variant="outlined"
                                error={!validName}
                                onChange={handleNameChange}
                            />
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                BIC/SWIFT
                            </FormLabel>
                            <TextField
                                id="bicswift"
                                variant="outlined"
                                onChange={(event) => setBranch({ ...branch, bicswift: event.target.value })}
                            />
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Address
                            </FormLabel>
                            <TextField
                                id="address"
                                variant="outlined"
                                onChange={(event) => setBranch({ ...branch, address: event.target.value })}
                            />
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Total assets
                            </FormLabel>
                            <TextField
                                id="total_assets"
                                variant="outlined"
                                onChange={(event) => setBranch({ ...branch, total_assets: parseInt(event.target.value) })}
                            />
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Total equity
                            </FormLabel>
                            <TextField
                                id="total_equity"
                                variant="outlined"
                                onChange={(event) => setBranch({ ...branch, total_equity: parseInt(event.target.value) })}
                            />
                        </Container>

                        <Button type="submit" variant="contained" sx={{ backgroundColor: colors.pink[500] }}>Add branch</Button>
                    </form>
                </CardContent>
            </Card>
        </React.Fragment>
    );
}