import { SetStateAction, useEffect, useState } from "react";
import ReadMoreIcon from "@mui/icons-material/ReadMore";
import EditIcon from "@mui/icons-material/Edit";
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";
import {
    Container,
    Table,
    TableHead,
    TableRow,
    TableCell,
    TableBody,
    IconButton,
    Tooltip,
    colors,
    Box,
    Pagination,
    CssBaseline,
} from "@mui/material";
import { Link } from "react-router-dom";
import { BACKEND_URL } from "../../utils";
import { BranchMenu } from "./BranchMenu";
import { Branch } from "../../models/Branch";
import React from "react";
import { useMediaQuery } from "react-responsive";

export const DisplayBranchList = () => {
    const [loading, setLoading] = useState(false);
    const [branch, setBranch] = useState([]);

    const isBigScreen = useMediaQuery({ query: "(min-width: 775px)" });

    useEffect(() => {
        setLoading(true);
        fetch(`${BACKEND_URL}/branch`)
            .then((response) => response.json())
            .then((data) => {
                setBranch(data);
                setLoading(false);
            });
    }, []);

    return (
        <React.Fragment>
            <CssBaseline />

            <BranchMenu />
            <h1>Branch list</h1>
            {!loading && branch.length === 0 && <div>No branches found.</div>}
            {isBigScreen && !loading && branch.length > 0 && (
                <>
                    <Table aria-label="simple table">
                        <TableHead>
                            <TableRow>
                                <TableCell align="center">#</TableCell>
                                <TableCell align="center">Name</TableCell>
                                <TableCell align="center">BIC/SWIFT</TableCell>
                                <TableCell align="center">Address</TableCell>
                                <TableCell align="center">Total assets</TableCell>
                                <TableCell align="center">Total equity</TableCell>
                                <TableCell align="center"></TableCell>
                                <TableCell align="center"></TableCell>
                            </TableRow>
                        </TableHead>

                        <TableBody>
                            {branch.map((branch: any, index) => (
                                <TableRow key={branch.id}>
                                    <TableCell align="center" component="th" scope="row">
                                        {index + 1}
                                    </TableCell>
                                    <TableCell align="center">{branch.name}</TableCell>
                                    <TableCell align="center">{branch.bicswift}</TableCell>
                                    <TableCell align="center">{branch.address}</TableCell>
                                    <TableCell align="center">
                                        {String(branch.total_assets)}
                                    </TableCell>
                                    <TableCell align="center">
                                        {String(branch.total_equity)}
                                    </TableCell>
                                    <TableCell align="center">
                                        <Box display="flex" justifyContent="center">
                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 1 }}
                                                to={`/branch/${branch.id}/details`}
                                            >
                                                <Tooltip title="View details of branch" arrow>
                                                    <ReadMoreIcon />
                                                </Tooltip>
                                            </IconButton>

                                            <IconButton
                                                component={Link}
                                                sx={{ mr: 1 }}
                                                to={`/branch/${branch.id}/update`}
                                            >
                                                <Tooltip title="Update branch data" arrow>
                                                    <EditIcon />
                                                </Tooltip>
                                            </IconButton>

                                            <IconButton
                                                component={Link}
                                                to={`/branch/${branch.id}/delete`}
                                            >
                                                <Tooltip title="Delete branch" arrow>
                                                    <DeleteForeverIcon />
                                                </Tooltip>
                                            </IconButton>
                                        </Box>
                                    </TableCell>
                                </TableRow>
                            ))}
                        </TableBody>
                    </Table>

                    <Box sx={{ mt: 2, textAlign: "center" }}>
                        <Pagination
                            color="primary"
                            size="large"
                            siblingCount={2}
                            sx={{ "& .MuiPaginationItem-textPrimary": { color: "#fff" } }}
                            showFirstButton
                            showLastButton
                            boundaryCount={2}
                        />
                    </Box>
                </>
            )}
            {!isBigScreen && !loading && branch.length > 0 && (
                <>
                    <Table aria-label="simple table">
                        <TableHead>
                            <TableRow>
                                <TableCell align="center">#</TableCell>
                                <TableCell align="center">Name</TableCell>
                                <TableCell align="center"></TableCell>
                            </TableRow>
                        </TableHead>

                        <TableBody>
                            {branch.map((branch: any, index) => (
                                <TableRow key={branch.id}>
                                    <TableCell align="center" component="th" scope="row">
                                        {index + 1}
                                    </TableCell>
                                    <TableCell align="center">{branch.name}</TableCell>
                                    <TableCell align="center">
                                        <IconButton
                                            component={Link}
                                            sx={{ mr: 3 }}
                                            to={`/branch/${branch.id}/details`}
                                        >
                                            <Tooltip title="View details of branch" arrow>
                                                <ReadMoreIcon />
                                            </Tooltip>
                                        </IconButton>

                                        <IconButton
                                            component={Link}
                                            sx={{ mr: 3 }}
                                            to={`/branch/${branch.id}/update`}
                                        >
                                            <Tooltip title="Update branch data" arrow>
                                                <EditIcon />
                                            </Tooltip>
                                        </IconButton>

                                        <IconButton
                                            component={Link}
                                            sx={{ mr: 3 }}
                                            to={`/branch/${branch.id}/delete`}
                                        >
                                            <Tooltip title="Delete branch" arrow>
                                                <DeleteForeverIcon />
                                            </Tooltip>
                                        </IconButton>
                                    </TableCell>
                                </TableRow>
                            ))}
                        </TableBody>
                    </Table>
                </>
            )}
        </React.Fragment>
    );
};

