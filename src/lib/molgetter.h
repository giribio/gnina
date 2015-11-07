/*
 * molgetter.h
 *
 *  Created on: Jun 5, 2014
 *      Author: dkoes
 */

#ifndef MOLGETTER_H_
#define MOLGETTER_H_

#include "model.h"
#include "obmolopener.h"
#include "flexinfo.h"

//this class abstracts reading molecules from a file
//we have three means of input:
//openbabel for general molecular data (default)
//vina parse_pdbqt for pdbqt files (one ligand, obey rotational bonds)
//smina format
class MolGetter
{
	model initm;
	enum Type {OB, PDBQT, SMINA,GNINA,NONE}; //different inputs

	Type type;
	path lpath;
	bool add_hydrogens;
	//openbabel data structs
	OpenBabel::OBConversion conv;
	obmol_opener infileopener;

	//smina data structs
	izfile infile;

	//pdbqt data
	bool pdbqtdone;

public:

	MolGetter(bool addH=true):  add_hydrogens(addH),
			 type(NONE), pdbqtdone(false) {
	}

	MolGetter(const std::string& rigid_name, const std::string& flex_name,
			FlexInfo& finfo, bool addH, tee& log):  add_hydrogens(addH),
			 type(NONE), pdbqtdone(false) {
		create_init_model(rigid_name, flex_name, finfo, log);
	}

	//create the initial model from the specified receptor files
	void create_init_model(const std::string& rigid_name,
			const std::string& flex_name, FlexInfo& finfo, tee& log);

	//setup for reading from fname
	void setInputFile(const std::string& fname);

	//initialize model to initm and add next molecule
	//return false if no molecule available;
	bool readMoleculeIntoModel(model &m);
};


#endif /* MOLGETTER_H_ */
