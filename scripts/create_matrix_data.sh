#!/bin/sh

JBLAS_LIB_NAME=jblas.jar

[ -z "$OAP_JBLAS_PATH" ] && echo "Variable OAP_JBLAS_PATH is not defined." && exit 1
[ ! -f "$OAP_JBLAS_PATH/$JBLAS_LIB_NAME" ] && echo "File jblas.jar does not exit in directory ${OAP_JBLAS_PATH}" && exit 2


groovy -cp $OAP_JBLAS_PATH/jblas.jar matrix_utils.groovy
