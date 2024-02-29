import { Autocomplete, Button, Card, CardActions, CardContent, Container, CssBaseline, FormLabel, IconButton, TextField, colors } from "@mui/material";
import { Link, useNavigate, useParams } from "react-router-dom";
import { BACKEND_URL } from "../../utils";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { useEffect, useState } from "react";
import { BranchMenu } from "./BranchMenu";
import { Branch } from "../../models/Branch";
import React from "react";


export const UpdateBranch = () => {
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

    useEffect(() => {
        setLoading(true);
        fetch(`${BACKEND_URL}/branch/${branchId}`).then(response => response.json()).then(data => {
            setBranch(data);
            setLoading(false);
        });
    }, [branchId]);

    const updateBranch = async (event: { preventDefault: () => void }) => {
        event.preventDefault();
        setLoading(true);
        fetch(`${BACKEND_URL}/branch/${branchId}`, {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(branch)
        }).then(response => {
            if (response.ok) {
                alert("Branch updated successfully.");
            } else {
                console.error('Error updating branch:', response.statusText);
                alert("Error updating branch: " + response.statusText);
            }
            navigate(`/branch`);
            setLoading(false);
        }).catch(error => {
            console.error('Error updating branch:', error);
            setLoading(false);
        });
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
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/branch`}>
                        <ArrowBackIcon />
                    </IconButton>{" "}
                    <form onSubmit={updateBranch} style={{ display: "flex", flexDirection: "column", padding: "8px" }}>
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
                    </form>
                </CardContent>
                <CardActions sx={{ justifyContent: "center" }}>
                    <Button type="submit" onClick={updateBranch} variant="contained" sx={{ backgroundColor: colors.pink[500] }}>Update</Button>
                    <Button onClick={handleCancel} variant="contained" sx={{ backgroundColor: colors.pink[500] }}>Cancel</Button>
                </CardActions>
            </Card>
        </React.Fragment>
    );
}