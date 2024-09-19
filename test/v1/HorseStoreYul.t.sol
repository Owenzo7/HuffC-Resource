// SPDX-License-Identifier: MIT

pragma solidity 0.8.20;

import {Base_testV1, IHorseStore} from "./Base_testV1.sol";
import {HorseStoreYul} from "../../src/horseStoreV1/HorseStoreYul.sol";

contract HorseStoreSolc is Base_testV1 {
    function setUp() public override {
        horseStore = IHorseStore(address(new HorseStoreYul()));
    }
}
