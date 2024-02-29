import { Autocomplete, Button, Card, CardActions, CardContent, Container, CssBaseline, FormLabel, IconButton, TextField, colors } from "@mui/material";
import { Link, useNavigate, useParams } from "react-router-dom";
import { BACKEND_URL } from "../../utils";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { useEffect, useState } from "react";
import { BankMenu } from "./BankMenu";
import { Bank } from "../../models/Bank";
import React from "react";


export const UpdateBank = () => {
    const { bankId } = useParams<{ bankId: string }>();
    const navigate = useNavigate();
    const [loading, setLoading] = useState(false);

    const [bank, setBank] = useState<Bank>({
        id: parseInt(String(bankId)),
        name: "",
        bicswift: "",
        headquarters: "",
        ceo: "",
        total_assets: 0,
        total_equity: 0,
    });

    const [validName, setValidName] = useState(true);
    const handleNameChange = (event: React.ChangeEvent<HTMLInputElement>) => {
        const name = event.target.value;
        setBank({ ...bank, name: name });
        setValidName(name.length >= 5);
    };

    useEffect(() => {
        setLoading(true);
        fetch(`${BACKEND_URL}/bank/${bankId}`).then(response => response.json()).then(data => {
            setBank(data);
            setLoading(false);
        });
    }, [bankId]);

    const updateBank = async (event: { preventDefault: () => void }) => {
        event.preventDefault();
        setLoading(true);
        fetch(`${BACKEND_URL}/bank/${bankId}`, {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(bank)
        }).then(response => {
            if (response.ok) {
                alert("Bank updated successfully.");
            } else {
                console.error('Error updating bank:', response.statusText);
                alert("Error updating bank: " + response.statusText);
            }
            navigate(`/bank`);
            setLoading(false);
        }).catch(error => {
            console.error('Error updating bank:', error);
            setLoading(false);
        });
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
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/bank`}>
                        <ArrowBackIcon />
                    </IconButton>{" "}
                    <form onSubmit={updateBank} style={{ display: "flex", flexDirection: "column", padding: "8px" }}>
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
                                onChange={(event) => setBank({ ...bank, bicswift: event.target.value })}
                            />
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Headquarters
                            </FormLabel>
                            <TextField
                                id="headquarters"
                                variant="outlined"
                                onChange={(event) => setBank({ ...bank, headquarters: event.target.value })}
                            />
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                CEO
                            </FormLabel>
                            <TextField
                                id="ceo"
                                variant="outlined"
                                onChange={(event) => setBank({ ...bank, ceo: event.target.value })}
                            />
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Total assets
                            </FormLabel>
                            <TextField
                                id="total_assets"
                                variant="outlined"
                                onChange={(event) => setBank({ ...bank, total_assets: parseInt(event.target.value) })}
                            />
                        </Container>

                        <Container sx={{ padding: "3px" }} style={{ display: "flex", flexDirection: "row", justifyContent: "space-around" }}>
                            <FormLabel style={{ marginTop: "15px", fontSize: "18px" }}>
                                Total equity
                            </FormLabel>
                            <TextField
                                id="total_equity"
                                variant="outlined"
                                onChange={(event) => setBank({ ...bank, total_equity: parseInt(event.target.value) })}
                            />
                        </Container>
                    </form>
                </CardContent>
                <CardActions sx={{ justifyContent: "center" }}>
                    <Button type="submit" onClick={updateBank} variant="contained" sx={{ backgroundColor: colors.pink[500] }}>Update</Button>
                    <Button onClick={handleCancel} variant="contained" sx={{ backgroundColor: colors.pink[500] }}>Cancel</Button>
                </CardActions>
            </Card>
        </React.Fragment>
    );
}