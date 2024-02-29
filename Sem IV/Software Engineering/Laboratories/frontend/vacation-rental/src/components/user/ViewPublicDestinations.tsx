import { useEffect, useState } from "react";
import AddIcon from '@mui/icons-material/Add';
import { Table, TableContainer, TableHead, TableRow, TableCell, TableBody, IconButton, Tooltip, colors, Box, Pagination, CssBaseline } from "@mui/material";
import { Link } from "react-router-dom";
import { UserMenu } from "./UserMenu";
import React from "react";
import { useMediaQuery } from "react-responsive";

export const ViewPublicDestinations = () => {
    const [loading, setLoading] = useState(false);
    const [destination, setDestination] = useState([]);

    const isBigScreen = useMediaQuery({ query: "(min-width: 775px)" });

    useEffect(() => {
        setLoading(true);
        // fetch(`${BACKEND_URL}/account`).then(response => response.json()).then(data => { setAccount(data); setLoading(false); });
    }, []);

    return (
        <React.Fragment>
            <CssBaseline />

            <UserMenu />
            <h1>Public Destinations</h1>
            {!loading && destination.length === 0 && <div>No destinations found.</div>}
            {isBigScreen && !loading &&
                destination.length > 0 && (
                    <><TableContainer style={{ backgroundColor: colors.grey[50] }}>
                        <Table sx={{ minWidth: 850 }} aria-label="simple table">
                            <TableHead>
                                <TableRow>
                                    <TableCell align="center">#</TableCell>
                                    <TableCell align="center">Geolocation</TableCell>
                                    <TableCell align="center">Title</TableCell>
                                    <TableCell align="center">Image</TableCell>
                                    <TableCell align="center">Description</TableCell>
                                    <TableCell align="center">Stay dates</TableCell>
                                </TableRow>
                            </TableHead>

                            <TableBody>
                                {destination.map((destination: any, index) => (
                                    <TableRow key={destination.id}>
                                        <TableCell align="center" component="th" scope="row">{index + 1}</TableCell>
                                        <TableCell align="center">{destination.geolocation}</TableCell>
                                        <TableCell align="center">{destination.title}</TableCell>
                                        <TableCell align="center">{destination.image}</TableCell>
                                        <TableCell align="center">{destination.description}</TableCell>
                                        <TableCell align="center">{destination.stay_dates}</TableCell>
                                        <TableCell align="center">
                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 3 }}
                                                to={`/bucket-list/add/public`}
                                            >
                                                <Tooltip title="Add to bucket list" arrow>
                                                    <AddIcon />
                                                </Tooltip>
                                            </IconButton>
                                        </TableCell>
                                    </TableRow>
                                ))}
                            </TableBody>
                        </Table>
                    </TableContainer>
                    </>
                )
            }
            {!isBigScreen && !loading &&
                destination.length > 0 && (
                    <>
                        <Table aria-label="simple table">
                            <TableHead>
                                <TableRow>
                                    <TableCell align="center">#</TableCell>
                                    <TableCell align="center">Title</TableCell>
                                    <TableCell align="center">Image</TableCell>
                                </TableRow>
                            </TableHead>

                            <TableBody>
                                {destination.map((destination: any, index) => (
                                    <TableRow key={destination.id}>
                                        <TableCell align="center" component="th" scope="row">{index + 1}</TableCell>
                                        <TableCell align="center">{destination.title}</TableCell>
                                        <TableCell align="center">{destination.image}</TableCell>
                                        <TableCell align="center">
                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 3 }}
                                                to={`/bucket-list/add/${destination.id}`}
                                            >
                                                <Tooltip title="Add to bucket list" arrow>
                                                    <AddIcon />
                                                </Tooltip>
                                            </IconButton>
                                        </TableCell>
                                    </TableRow>
                                ))}
                            </TableBody>
                        </Table>
                    </>
                )
            }
        </React.Fragment>
    )
}