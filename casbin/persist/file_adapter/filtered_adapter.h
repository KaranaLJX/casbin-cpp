#ifndef CASBIN_CPP_PERSIST_FILE_ADAPTER_FILTERED_ADAPTER
#define CASBIN_CPP_PERSIST_FILE_ADAPTER_FILTERED_ADAPTER

#include "file_adapter.h"

// Filter defines the filtering rules for a FilteredAdapter's policy. Empty values
// are ignored, but all others must match the filter.
class Filter{
    public:
        vector<string> P;
        vector<string> G;
};

class FilteredAdapter : public FileAdapter {
    private:

        static bool filterLine(string line, Filter* filter);

        static bool filterWords(vector<string> line, vector<string> filter);

        void loadFilteredPolicyFile(Model* model, Filter* filter, void (*handler)(string, Model*));

    public:

        // NewFilteredAdapter is the constructor for FilteredAdapter.
        static FilteredAdapter* NewFilteredAdapter(string file_path);

        // LoadPolicy loads all policy rules from the storage.
        void LoadPolicy(Model* model);

        // LoadFilteredPolicy loads only policy rules that match the filter.
        void LoadFilteredPolicy(Model* model, Filter* filter);

        // IsFiltered returns true if the loaded policy has been filtered.
        bool IsFiltered();

        // SavePolicy saves all policy rules to the storage.
        void SavePolicy(Model* model);
};

#endif